setwd("C:\\Users\\kyle0\\Desktop\\Git\\Individual-Study\\R for Qunat-study")
library(quantmod)
library(PerformanceAnalytics)
library(magrittr)

ticker = c('SPY','TLT')
getSymbols(ticker)
prices = do.call(cbind,lapply(ticker,function(x)Ad(get(x))))
rets = Return.calculate(prices)%>%na.omit()
cor(rets)
portfolio = Return.portfolio(R= rets,
                             weights = c(0.6,0.4),
                             rebalance_on = 'years',
                             verbose = TRUE)

portfolios = cbind(rets, portfolio$returns)%>%
  setNames(c('주식','채권','60대40'))

charts.PerformanceSummary(portfolios, main = "60대40 포트폴리오")

turnover = xts(
  rowSums(abs(portfolio$BOP.Weight - timeSeries::lag(portfolio$EOP.Weight)),
          na.rm=TRUE),
  order.by = index(portfolio$BOP.Weight)
)
#lag 함수 : 한 단계씩 끌어내림.
chart.TimeSeries(turnover)

#시점선택 전략 백테스팅
library(quantmod)
library(PerformanceAnalytics)

symbols = c('SPY','SHY') #shy : 미국 단기채 수익률 추종 ETF
getSymbols(symbols)
prices = do.call(cbind,lapply(symbols,function(x)Ad(get(x))))
rets = na.omit(Return.calculate(prices))
ep = endpoints(rets, on = 'months') #rets의 월별 말일의 위치를 반환
wts = list() #weights를 넣을 빈 리스트 생성
lookback = 10 #n개월 이동평균 값

i = lookback + 1
sub_price = prices[ep[i-lookback]:ep[i],1]
head(sub_price,3)
sma = mean(sub_price)
wt = rep(0,2)
wt[1] = ifelse(last(sub_price)>sma,1,0) #주식 비중
wt[2] = 1 - wt[1] #현금 비중 = 1 - 주식비중

#반복하면서 전체기간에 적용
wts = list()
for (i in (lookback + 1): length(ep)){
  sub_price = prices[ep[i-lookback]: ep[i],1]
  sma = mean(sub_price)
  wt = rep(0,2)
  wt[1] = ifelse(last(sub_price)>sma,1,0)
  wt[2] = 1 - wt[1]
  wts[[i]] = xts(t(wt),order.by = index(rets[ep[i]]))
}
wts = do.call(rbind,wts)
Tactical = Return.portfolio(rets,wts, verbose = TRUE)
portfolios = na.omit(cbind(rets[,1],Tactical$returns))%>%
  setNames(c('매수 후 보유','시점 선택 전략'))
charts.PerformanceSummary(portfolios,main=
                            "BUY & HOLD vs Tactical")

#동적 자산 배분
#1)과거 12개월 수익률이 높은 5개 자산 선택
#2)최소분산 포트폴리오를 구성하며, 개별 투자비중은 10~30% 사이로만
#3)매월 리밸런싱

library(quantmod)
library(PerformanceAnalytics)
library(RiskPortfolios)
library(tidyr)
library(dplyr)
library(ggplot2)

symbols = c('SPY', #미국 주식
            'IEV', #유럽 주식
            'EWJ', #일본 주식
            'EEM', #이머징 마켓
            'TLT', #미국 장기채
            'IEF', #미국 중기채
            'IYR', #미국 리츠
            'VNQ', #글로벌 리츠
            'GLD', #금
            'DBC') #상품
getSymbols(symbols, src = 'yahoo')
prices = do.call(cbind,lapply(symbols, function(x)Ad(get(x))))%>%
  setNames(symbols)
rets = Return.calculate(prices)%>%na.omit()
ep = endpoints(rets, on = 'months')
wts = list()
lookback = 12
wt_zero = rep(0,10)%>%setNames(colnames(rets))

for(i in (lookback + 1):length(ep)){
  sub_ret = rets[ep[i-lookback]:ep[i],]
  cum = Return.cumulative(sub_ret)
  K=rank(-cum)<=5
  covmat = cov(sub_ret[,K])
  wt = wt_zero
  wt[K] = optimalPortfolio(covmat,
                           control = list(type = 'minvol',
                                          constraint = 'user',
                                          LB = rep(0.1,5),
                                          UB = rep(0.3,5)))
  wts[[i]] = xts(t(wt),order.by = index(rets[ep[i]]))
}
wts = do.call(rbind,wts)

GDAA = Return.portfolio(rets, wts, verbose = TRUE)
charts.PerformanceSummary(GDAA$returns,main = '동적 자산 배분')

wts%>%fortify.zoo()%>%
  gather(key,value,-Index)%>%
  mutate(Index = as.Date(Index))%>%
  mutate(key = factor(key,levels = unique(key)))%>%
  ggplot(aes(x=Index,y=value))+
  geom_area(aes(color = key, fill=key),
            position = 'stack')+
  xlab(NULL)+ylab(NULL)+theme_bw()+
  scale_x_date(date_breaks = "years",date_labels = "%Y", expand = c(0,0))+
  scale_y_continuous(expand = c(0,0))+
  theme(plot.title = element_text(hjust = 0.5,
                                  size = 12),
        legend.position = 'bottom',
        legend.title = element_blank(),
        axis.text.x = element_text(angle = 45, hjust = 1, size = 8),
        panel.grid.minor.x = element_blank())+
  guides(color = guide_legend(byrow=TRUE))

GDAA$turnover = xts(
  rowSums(abs(GDAA$BOP.Weight - timeSeries::lag(GDAA$EOP.Weight)),
          na.rm=TRUE),
  order.by = index(GDAA$BOP.Weight)
)

chart.TimeSeries(GDAA$turnover)
fee = 0.0030
GDAA$net = GDAA$returns - GDAA$turnover*fee

cbind(GDAA$returns, GDAA$net)%>%
  setNames(c('No Fee','After Fee'))%>%
  charts.PerformanceSummary(main = 'GDAA')