#베타 계산
library(quantmod)
library(PerformanceAnalytics)
library(magrittr)

symbols = c('102110.KS','039490.KS')
getSymbols(symbols)

prices = do.call(cbind,lapply(symbols,function(x)Cl(get(x))))
ret = Return.calculate(prices)
ret = ret['2016-01::2018-12']

rm = ret[,1]
ri=ret[,2]

reg = lm(ri ~ rm)
summary(reg)

plot(as.numeric(rm),as.numeric(ri),pch = 4, cex = 0.3,
     xlab = "KOSPI 200", ylab = "Individual Stock",
     xlim = c(-0.02,0.02),ylim = c(-0.02,0.02))
#pch는 점들의 모양, cex는 점들의 크기.
abline(a=0,b=1,lty=2)#a는 상수, b는 직선의 기울기, lty는 선의 유형
abline(reg,col = 'red')

#저변동성 전략
##일간기준
library(stringr)
library(xts)
library(PerformanceAnalytics)
library(magrittr)
library(ggplot2)
library(dplyr)

KOR_price = read.csv('data/KOR_price.csv',row.names=1,
                     stringsAsFactors = FALSE)%>%as.xts()
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names = 1,
                      stringsAsFactors = FALSE)
KOR_ticker$종목코드 = str_pad(KOR_ticker$종목코드,6,'left',0)
ret = Return.calculate(KOR_price)
std_12m_daily = xts::last(ret,252) %>% apply(.,2,sd)%>%
  multiply_by(sqrt(252))
#xts::last : dplyr패키지에도 last 함수가 있어서 xts의 last임을 명시
#last(a,b): a데이터에서 마지막 b개 만큼의 데이터를 가져옴. 이 경우는 252개(1년 영업일)
#apply(dataset,row(1) or col(2),function)
std_12m_daily %>%
  data.frame()%>%
  ggplot(aes(x=(.)))+
  geom_histogram(binwidth=0.01)+
  annotate("rect",xmin=-0.02,xmax = 0.02,
           ymin = 0,
           ymax=sum(std_12m_daily == 0, na.rm = TRUE)*1.1,
           alpha = 0.3, fill="red")+
  xlab(NULL)
std_12m_daily[std_12m_daily ==0]=NA #1년간 거래 정지로 인해 변동성이 0으로 나오는 것들은 NA로 처리
std_12m_daily[rank(std_12m_daily)<=30] #변동성이 낮은 순서로 30개 뽑아냄.
std_12m_daily[rank(std_12m_daily)<=30]%>%
  data.frame()%>%
  ggplot(aes(x=rep(1:30),y=.))+
  geom_col()+
  xlab(NULL)

invest_lowvol= rank(std_12m_daily) <=30
KOR_ticker[invest_lowvol,]%>%
  select(`종목코드`,`종목명`) %>%
  mutate(변동성 = round(std_12m_daily[invest_lowvol],4))

#저변동성 포트폴리오 구하기: 주간 기준
std_12m_weekly = xts::last(ret, 252)%>%
  apply.weekly(Return.cumulative)%>%
  apply(.,2,sd) %>%multiply_by(sqrt(52))
std_12m_weekly[std_12m_weekly==0]=NA
std_12m_weekly[rank(std_12m_weekly)<=30]
invest_lowvol_weekly = rank(std_12m_weekly)<=30
KOR_ticker[invest_lowvol_weekly,]%>%
  select(종목코드, 종목명)%>%
  mutate(변동성 = round(std_12m_weekly[invest_lowvol_weekly],4))

intersect(KOR_ticker[invest_lowvol,'종목명'],
          KOR_ticker[invest_lowvol_weekly,'종목명'])

##모멘텀 전략
#12개월 모멘텀
library(stringr)
library(xts)
library(PerformanceAnalytics)
library(magrittr)
library(dplyr)

KOR_price = read.csv('data/KOR_price.csv',row.names=1,
                     stringsAsFactors = FALSE)%>%as.xts()
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names = 1,
                      stringsAsFactors = FALSE)
KOR_ticker$종목코드 = str_pad(KOR_ticker$종목코드,6,'left',0)

ret = Return.calculate(KOR_price)%>% xts::last(252)
ret_12m = ret %>% sapply(.,function(x){
  prod(1+x)-1}) #누적 수익률 계산
ret_12m[rank(-ret_12m)<=30] #rank(-ret_12m) 내림차순 정렬

invest_mom = rank(-ret_12m) <= 30
KOR_ticker[invest_mom,]%>%
  select(종목코드, 종목명)%>%
  mutate(수익률 = round(ret_12m[invest_mom],4))

#위험조정 수익률
ret = Return.calculate(KOR_price)%>%xts::last(252)
ret_12m = ret %>% sapply(.,function(x){
  prod(1+x)-1
})
std_12m = ret %>%apply(.,2,sd)%>%multiply_by(sqrt(252))
sharpe_12m = ret_12m/std_12m

invest_mom_sharpe = rank(-sharpe_12m)<=30
KOR_ticker[invest_mom_sharpe,] %>%
  select(종목코드, 종목명)%>%
  mutate(수익률 = round(ret_12m[invest_mom_sharpe],2),
            변동성 = round(std_12m[invest_mom_sharpe],2),
            위험조정수익률 = round(sharpe_12m[invest_mom_sharpe],2))%>%
  as_tibble()%>%
  print(n=Inf) #tibble형태로 변환해서 조금 더 깔끔하게 콘솔에서 확인함.

intersect(KOR_ticker[invest_mom,'종목명'],
          KOR_ticker[invest_mom_sharpe,'종목명'])

#시각화
library(xts)
library(ggplot2)
library(tidyr)

KOR_price[, invest_mom_sharpe]%>%
  fortify.zoo()%>% #zoo 데이터를 데이터 프레임으로 전환
  gather(ticker,price,-Index)%>% #와이드 형태의 데이터를 롱데이터 프레임으로 변환
  ggplot(aes(x=Index,y=price))+
  geom_line()+
  facet_wrap(.~ticker,scales='free')+
  xlab(NULL)+
  ylab(NULL)+
  theme(axis.text.x = element_blank(),
        axis.text.y = element_blank())

##밸류 전략
#저PBR 포트폴리오
library(stringr)
library(ggplot2)
library(dplyr)

KOR_value = read.csv('data/KOR_value.csv',row.names = 1,
                     stringsAsFactors = FALSE)
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names=1,stringsAsFactors = FALSE)
KOR_ticker$종목코드 = str_pad(KOR_ticker$종목코드,6,'left',0)

invest_pbr = rank(KOR_value$PBR)<=30
KOR_ticker[invest_pbr,]%>%
  select(종목코드, 종목명)%>%
  mutate(PBR = round(KOR_value[invest_pbr,'PBR'],4))

#각 지표 결합하기
library(corrplot)
rank_value = KOR_value %>%
  mutate_all(list(~min_rank(.)))

cor(rank_value,use='complete.obs')%>%
  round(.,2)%>%
  corrplot(method = 'color', type = 'upper',
           addCoef.col = 'black', number.cex = 1,
           tl.cex = 0.6, tl.srt = 45, tl.col = 'black',
           col = colorRampPalette(c('blue','white','red'))(200),
           mar= c(0,0,0.5,0))

rank_sum = rank_value %>%
  rowSums() #종목별 랭키들의 합

invest_value = rank(rank_sum)<=30 #네 개 지표 랭킹의 합 기준 랭킹이 낮은 30종목 선택
KOR_ticker[invest_value,]%>%
  select(종목코드,종목명)%>%
  cbind(round(KOR_value[invest_value,],2))

intersect(KOR_ticker[invest_pbr,'종목명'],
          KOR_ticker[invest_value,'종목명'])

##펀더맨탈 전략(퀄리티 전략)
#F-score
library(stringr)
library(ggplot2)
library(dplyr)

KOR_fs = readRDS('data/KOR_fs.Rds')
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names=1,
                      stringsAsFactors = FALSE)
KOR_ticker$종목코드= str_pad(KOR_ticker$종목코드,6,'left',0)

#Profitability
ROA = KOR_fs$지배주주순이익 / KOR_fs$자산
CFO = KOR_fs$영업활동으로인한현금흐름/KOR_fs$자산
ACCRUAL = CFO - ROA

#Financial Performance
LEV = KOR_fs$장기차입금 / KOR_fs$자산
LIQ = KOR_fs$유동자산 / KOR_fs$유동부채
OFFER = KOR_fs$유상증자

#Operational Efficiency
MARGIN = KOR_fs$매출총이익/KOR_fs$매출액
TURN = KOR_fs$매출액/KOR_fs$자산

if (lubridate::month(Sys.Date()) %in% c(1,2,3,4)){
  num_col = str_which(colnames(KOR_fs[[1]]),paste0("X",as.character(lubridate::year(Sys.Date())-2),".12"))
}else{
  num_col = str_which(colnames(KOR_fs[[1]]),paste0("X",as.character(lubridate::year(Sys.Date())-1),".12"))
}
F_1 = as.integer(ROA[,num_col]>0)
F_2 = as.integer(CFO[,num_col]>0)
F_3 = as.integer(ROA[,num_col]-ROA[,(num_col-1)]>0)
F_4 = as.integer(ACCRUAL[,num_col]>0)
F_5 = as.integer(LEV[,num_col]-LEV[,(num_col-1)]<=0)
F_6 = as.integer(LIQ[,num_col] - LIQ[,num_col]>0)
F_7 = as.integer(is.na(OFFER[,num_col])|OFFER[,num_col] <=0)
F_8 = as.integer(MARGIN[,num_col] - MARGIN[,(num_col-1)]>0)
F_9 = as.integer(TURN[,num_col] - TURN[,(num_col-1)]>0)
#as.integer : 함수 안의 조건이 true이면 1, false이면 0을 반환

F_Table = cbind(F_1,F_2,F_3,F_4,F_5,F_6,F_7,F_8,F_9)
F_Score = F_Table %>%
  apply(.,1,sum,na.rm = TRUE)%>%
  setNames(KOR_ticker$종목명)
(F_dist = prop.table(table(F_Score))%>%round(3))
F_dist %>%
  data.frame()%>%
  ggplot(aes(x=F_Score,y=Freq,
             label = paste0(Freq*100,'%')))+
  geom_bar(stat = 'identity')+
  geom_text(color = 'black',size=3,vjust = -0.4)+
  scale_y_continuous(expand=c(0,0,0,0.05),
                     labels = scales::percent)+
  ylab(NULL)+
  theme_classic()

invest_F_Score = F_Score %in% c(8)
KOR_ticker[invest_F_Score,]%>%
  select(종목코드,종목명)%>%
  mutate(`F-Score` = F_Score[invest_F_Score])

#각 지표 결합하기
library(stringr)
library(ggplot2)
library(dplyr)
library(tidyr)

KOR_fs = readRDS('data/KOR_fs.Rds')
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names=1,
                      stringsAsFactors = FALSE)
KOR_ticker$종목코드= str_pad(KOR_ticker$종목코드,6,'left',0)

if (lubridate::month(Sys.Date()) %in% c(1,2,3,4)){
  num_col = str_which(colnames(KOR_fs[[1]]),paste0("X",as.character(lubridate::year(Sys.Date())-2),".12"))
}else{
  num_col = str_which(colnames(KOR_fs[[1]]),paste0("X",as.character(lubridate::year(Sys.Date())-1),".12"))
}

quality_roe = (KOR_fs$지배주주순이익/KOR_fs$자본)[num_col]
quality_gpa = (KOR_fs$매출총이익/KOR_fs$자산)[num_col]
quality_cfo = (KOR_fs$영업활동으로인한현금흐름/KOR_fs$자산)[num_col]

quality_profit = cbind(quality_roe,quality_gpa,quality_cfo)%>%
  setNames(.,c('ROE','GPA','CFO'))

rank_quality = quality_profit%>%
  mutate_all(list(~min_rank(desc(.))))

cor(rank_quality,use='complete.obs')%>%
  round(.,2)%>%
  corrplot(method='color',type='upper',addCoef.col = 'black',number.cex = 1,
           tl.cex = 0.6, tl.srt = 45, tl.col = 'black',
           col = 
             colorRampPalette(c('blue','white','red'))(200),
           mar=c(0,0,0.5,0))

rank_sum = rank_quality %>%
  rowSums()

invest_quality = rank(rank_sum)<=30
KOR_ticker[invest_quality,]%>%
  select(종목코드,`종목명`)%>%
  cbind(round(quality_profit[invest_quality,],4))