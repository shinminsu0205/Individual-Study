setwd("C:\\Users\\kyle0\\Desktop\\Git\\Individual-Study\\R for Qunat-study")
library(quantmod)
library(PerformanceAnalytics)
library(magrittr)

symbols=c('SPY','IEV','EEM','TLT','IEF',
          'IYR','RMX','GLD','DBC','EWJ')
getSymbols(symbols,src = 'yahoo')
prices = do.call(cbind,lapply(symbols,function(x)Ad(get(x))))%>%
  setNames(symbols)

rets = Return.calculate(prices)%>%na.omit()

library(tidyr)
library(dplyr)
library(corrplot)

cor(rets)%>%
  corrplot(method = 'color',type = 'upper',
           addCoef.col = 'black', number.cex = 0.7,
           tl.cex = 0.6, tl.srt = 45, tl.col = 'black',
           col = colorRampPalette(c('blue','white','red'))(200),
           mar = c(0,0,0.5,0))

covmat = cov(rets)

#최소분산 포트폴리오 목적함수 : 1/2*w'(cov-matrix)w, where w is wight of the each element
##slsqp 함수를 이용한 최적화
  ##목적함수 : min f(x)
  ##제약조건 : b(x) >=0, c(x)=0
  ##slsqp(x0, fn, gr, lower, upper, hin, hinjac, heq, heqjac, nl.info, control = list())
  ## x0 : 초기값, 일반적으로 모든 x에 대해 동일한 값을 넣음
  ## fn : 최소화하고자 하는 목적함수
  ## hin : 부등위 제약 조건(b(x)) 자동적으로 hin>=0으로 인식함.
  ## heq : 등위 제약 조건(c(x)) 자동적으로 heq ==0으로 인식함.(-1을 입력하면 heq == 1로 인식)

objective = function(w){
  obj = t(w) %*% covmat %*% w
  return (obj)
}

hin.objective = function(w){
  return (w) ## w>=0
}

heq.objective = function(w){
  sum_w = sum(w)
  return (sum_w - 1) ##sum_w -1 ==0
}

library(nloptr)

result = slsqp(x0=rep(0.1,10),
               fn = objective,
               hin = hin.objective,
               heq = heq.objective)
print(result$par)
print(result$value)

w_1 = result$par %>% round(.,4)%>%
  setNames(colnames(rets))

print(w_1)

##solve.QP()함수를 이용한 최적화
  ##목적함수: min(-d'b+1/2b'Db), where b is the weight of each asset and D is the cov-matrix
  ##제약조건: A'b >= b0(항상 좌변이 큰 형태이므로 작게 만들기 위해서는 -를 곱해준다.)
  ##solve.QP(Dmat, dvec, Amat, bvec, meq = 0, factorized = FALSE)
  ##Dmat = D
  ##dvec = d, 포트폴리오 최적화에서는 의미없음.
  ##Amat = A', transpose 행렬을 넣어줘야 한다는 점 유의.//가장 중요함.
  ##bvec = b0
  ##meq = bvec의 몇 번째까지를 등위 제약 조건으로 할지 확인하는 부분.

Dmat = covmat
dvec = rep(0,10)
Amat = t(rbind(rep(1,10),diag(10),-diag(10)))
bvec = c(1,rep(0,10),-rep(1,10))
meq = 1

library(quadprog)
result = solve.QP(Dmat, dvec, Amat, bvec, meq)

print(result$solution) ##최적값
print(result$value) ##분산
w_2 = result$solution %>%round(.,4)%>%
  setNames(colnames(rets))

print(w_2)

##optimalPortfolio()함수를 이용한 최적화
  ##optimalPortfolio(Sigma, mu=NULL,semiDev = NULL, control = list())
  ##control 인자(type)
  ###minvol : 최소분산
  ###invvol : 역변동성
  ###erc : 위험균형
  ###maxdiv : 최대분산효과
  ###riskeff:위험-효율적 포트폴리오
  ##control인자(constraint)
  ###lo : 최소 투자비중이 0보다 클 것
  ###user : 최소(LB)및 최대(UB) 투자비중 결정

library(RiskPortfolios)
w_3 = optimalPortfolio(covmat, control = list(type = 'minvol',
                                              constraint = 'lo'))%>%
  round(.,4)%>%
  setNames(colnames(rets))

print(w_3)

##결괏값 확인 --> 특정 종목에 지나치게 치중
library(ggplot2)

data.frame(w_1)%>%
  ggplot(aes(x=factor(rownames(.),levels = rownames(.)),
             y= w_1))+
  geom_col()+
  xlab(NULL)+ylab(NULL)

## 최소 및 최대 투자비중 제약조건 추가(slsqp)
result = slsqp(x0=rep(0.1,10),
               fn = objective,
               hin = hin.objective,
               heq = heq.objective,
               lower = rep(0.05, 10),
               upper = rep(0.2,10))
w_4 = result$par %>% round(.,4)%>%
  setNames(colnames(rets))

## 최소 및 최대 투자비중 제약조건 추가(solve.QP)
Dmat = covmat
dvec = rep(0,10)
Amat = t(rbind(rep(1,10),diag(10),-diag(10)))
bvec = c(1,rep(0.05,10),-rep(0.2,10))
meq = 1
result = solve.QP(Dmat, dvec, Amat, bvec, meq)

## 최소 및 최대 투자비중 제약조건 추가(optimalPortfolio)
w_6 = optimalPortfolio(covmat, control = list(type = 'minvol',
                                              constraint = 'user',
                                              LB = rep(0.05, 10),
                                              UB = rep(0.2,10)))%>%
  round(.,4)%>%
  setNames(colnames(rets))

print(w_6)

data.frame(w_4)%>%
  ggplot(aes(x=factor(rownames(.),levels = rownames(.)),y=w_4))+
  geom_col()+
  geom_hline(aes(yintercept = 0.05),color = 'red')+
  geom_hline(aes(yintercept = 0.2), color = 'red')+
  xlab(NULL)+ylab(NULL)

##각 자산별 제약조건 추가 slsqp랑 optimalportfolio는 힘듦
Dmat = covmat
dvec = rep(0,10)
Amat = t(rbind(rep(1,10),diag(10),-diag(10)))
bvec = c(1,c(0.1,0.1,0.05,0.05,0.1,
             0.1,0.05,0.05,0.03,0.03),
         -c(0.25,0.25,0.2,0.2,0.2,0.2,0.1,0.1,0.08,0.08))
meq = 1
result = solve.QP(Dmat,dvec,Amat,bvec,meq)
result$solution%>%
  round(.,4)%>%
  setNames(colnames(rets))

#최대 분산효과 포트폴리오
##Duality를 활용하여 최대 분산효과 만들기
  ##목적함수 : min(1/2w'(covmatrix)w)
  ##제약조건 : sum(w'sigmamatrix)=1, for all w >=0
  ##solve.QP()
Dmat = covmat
dvec = rep(0,10)
Amat = t(rbind(sqrt(diag(covmat)),diag(10)))
bvec = c(1,rep(0,10))
meq = 1

result = solve.QP(Dmat,dvec,Amat,bvec,meq)
w = result$solution%>%
  round(.,4)%>%
  setNames(colnames(rets))
print(w)
w = (w/sum(w))%>%
  round(.,4)
print(w)

data.frame(w)%>%
  ggplot(aes(x=factor(rownames(.),levels=rownames(.)),y=w))+
  geom_col()+
  geom_col()+
  xlab(NULL)+ylab(NULL)

##optimalportfolio활용(Min -DR 방법)
w=optimalPortfolio(covmat,control = list(type = 'maxdiv',
                                         constraint = 'lo'))%>%
  round(.,4)

##duality 최소 및 최대 투자 비중 제약조건
  ##최소 투자 비중 조건:(-lb X e' + I)w >=0 where e is the element matrix, which means all of its elements are 1
  ##최대 투자 비중 조건:(ub X e' - I)w >= 0

Dmat = covmat
dvec = rep(0,10)
Alb = -rep(0.05, 10)%*%matrix(1,1,10) + diag(10)
Aub = rep(0.2,10)%*%matrix(1,1,10) - diag(10)
Amat = t(rbind(sqrt(diag(covmat)),Alb, Aub))
bvec = c(1,rep(0,10),rep(0,10))
meq = 1

result = solve.QP(Dmat,dvec,Amat,bvec,meq)
w = result$solution
w = (w/sum(w))%>%
  round(.,4)%>%
  setNames(colnames(rets))
print(w)

data.frame(w)%>%
  ggplot(aes(x=factor(rownames(.),levels = rownames(.)),
             y=w))+
  geom_col()+
  geom_hline(aes(yintercept = 0.05),color = 'red')+
  geom_hline(aes(yintercept = 0.2),color = 'red')+
  xlab(NULL)+ylab(NULL)

##각 자산별 제약 조건 추가
Dmat = covmat
dvec = rep(0,10)
Alb = -c(0.1,0.1,0.05,0.05,0.1,
         0.1,0.05,0.05,0.03,0.03)%*%
  matrix(1,1,10) + diag(10)
Aub = c(0.25,0.25,0.2,0.2,0.2,
        0.2,0.1,0.1,0.08,0.08)%*%
  matrix(1,1,10)-diag(10)
Amat = t(rbind(sqrt(diag(covmat)),Alb,Aub))
bvec = c(1,rep(0,10),rep(0,10))
meq = 1

result = solve.QP(Dmat,dvec,Amat,bvec,meq)

w = result$solution
w= (w/sum(w))%>%
  round(.,4)%>%
  setNames(colnames(rets))
print(w)

#위험균형 포트폴리오
get_RC = function(w, covmat){
  port_vol = t(w)%*%covmat%*%w
  port_std = sqrt(port_vol)
  
  MRC = (covmat %*% w) / as.numeric(port_std)
  RC = MRC * w
  RC = c(RC/sum(RC))
  
  return(RC)
}
ret_stock_bond = rets[,c(1,4)]
cov_stock_bond = cov(ret_stock_bond)
RC_stock_bond = get_RC(c(0.6,0.4),cov_stock_bond)
RC_stock_bond = round(RC_stock_bond,4)
print(RC_stock_bond)

##rp 함수를 통한 최적화 --> slsqp, optimalPortfolio도 가능은 한데 가끔 최적화가 안 됨.
  ##rp(x0,P,mrc)
    ## x0 : 초기값
    ## P:공분산 매트릭스
    ##mrc : 목표로 하는 각 자산별 위험기여도 값.
library(cccp)
opt = rp(x0 = rep(0.1,10),
         P=covmat,
         mrc = rep(0.1,10))
w = getx(opt)%>%drop() #벡터로 전환
w = (w/sum(w))%>%
  round(.,4)%>%
  setNames(colnames(rets))
print(w)

get_RC(w,covmat) #rmx는 상폐돼서 값이 이상하게 나옴.

##위험예산 포트폴리오
opt = rp(x0 = rep(0.1,10),
         P=covmat,
         mrc = c(0.15,0.15,0.15,0.15,0.1,
                 0.1,0.05,0.05,0.05,0.05))
w = getx(opt)%>%drop()
w = (w/sum(w))%>%
  round(.,4)%>%
  setNames(colnames(rets))
print(w)

#인덱스 포트폴리오
library(stringr)
library(dplyr)

KOR_ticker = read.csv('data/KOR_ticker.csv', row.names = 1, stringsAsFactors = FALSE)
KOSPI200 = KOR_ticker %>% filter(시장구분 == 'KOSPI')%>%
  slice(1:200)%>%
  mutate(시가총액비중 = 시가총액/sum(시가총액))

library(ggplot2)
KOSPI200%>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y=시가총액비중))+
  geom_point()+
  xlab('종목명')+
  ylab('시가총액비중(%)')+
  scale_y_continuous(labels = scales::percent)

KOSPI200%>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y = 시가총액비중))+
  geom_point()+
  xlab('종목명')+
  ylab('시가총액비중(로그스케일링)')+
  scale_y_log10()+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by = 5),'종목명'])+
  theme(axis.text.x = element_text(angle = 60, hjust = 1))

KOSPI200 = KOSPI200 %>%
  mutate(매수금액 = 100000000 * 시가총액비중,
             매수주수 = 매수금액 / 종가)
KOSPI200 %>% select(매수금액, 매수주수)%>%head()
KOSPI200 = KOSPI200 %>% mutate(매수주수 = floor(매수주수)) #소숫점을 내림을 통해서 제거
KOSPI200 %>% select(매수금액, 매수주수)%>%head()

inv_money = KOSPI200 %>% mutate(실제매수금액 = 종가 * 매수주수)%>%
  summarize(sum(실제매수금액))

print(inv_money)

#팩터를 이용한 인핸스드 포트폴리오 구성
KOSPI200 = KOSPI200 %>% select(종목명, PBR, 시가총액비중)%>%
  mutate(PBR = as.numeric(PBR))
##단순 가감법
KOSPI200 = KOSPI200 %>%
  mutate(랭킹 = rank(PBR),
           조절비중 = ifelse(랭킹 <= 100, 시가총액비중 + 0.0005,
                           시가총액비중 - 0.0005),
           조절비중 = ifelse(조절비중 < 0, 0, 조절비중),
           조절비중 = 조절비중 / sum(조절비중),
           차이 = 조절비중 - 시가총액비중)
library(tidyr)

head(KOSPI200)

KOSPI200%>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y = 시가총액비중))+
  geom_point()+
  geom_point(data = KOSPI200,aes(x=reorder(종목명,-시가총액비중),y = 조절비중),
             color = 'red', shape = 4)+
  xlab('종목명')+
  ylab('비중(%)')+
  coord_cartesian(ylim = c(0,0.03))+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by = 5),'종목명'])+
  scale_y_continuous(labels = scales::percent)+
  theme(axis.text.x = element_text(angle=60,hjust = 1))

KOSPI200_mod = KOSPI200%>%arrange(PBR)

KOSPI200_mod%>%
  ggplot(aes(x=reorder(종목명,PBR),y=차이))+
  geom_point()+
  geom_col(aes(x=reorder(종목명, PBR),y=PBR/10000),fill = 'blue', alpha = 0.2)+
  xlab('종목명')+
  ylab('차이(%)')+
  scale_y_continuous(labels = scales::percent,
                     sec.axis = sec_axis(~.*10000,name="PBR"))+
  scale_x_discrete(breaks = KOSPI200_mod[seq(1,200,by=10),'종목명'])+
  theme(axis.text.x = element_text(angle = 60, hjust=1))

#팩터 틸트 포트폴리오
KOSPI200_tilt = KOSPI200%>%
  select(종목명, PBR, 시가총액비중, 랭킹)%>%
  mutate(zscore = -scale(랭킹),
         cdf = pnorm(zscore),
         투자비중 = 시가총액비중 * cdf,
         투자비중 = 투자비중 / sum(투자비중),
         차이 = 투자비중 - 시가총액비중)
head(KOSPI200_tilt)

KOSPI200%>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y=시가총액비중))+
  geom_point()+
  geom_point(data=KOSPI200_tilt,aes(x=reorder(종목명, -시가총액비중),y=투자비중),
             color = 'red',shape = 4)+
  xlab('종목명')+
  ylab('비중(%)')+
  coord_cartesian(ylim=c(0,0.03))+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by=5),'종목명'])+
  scale_y_continuous(labels = scales::percent)+
  theme(axis.text.x = element_text(angle = 60, hjust=1))

##제약을 거는 경우
KOSPI200_tilt%>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y=차이))+
  geom_point()+
  geom_hline(aes(yintercept = 0.005),color = 'red')+
  geom_hline(aes(yintercept = -0.005), color = 'red')+
  xlab('종목명')+
  ylab('비중차이(%)')+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by=5),'종목명'])+
  scale_y_continuous(labels = scales::percent)+
  theme(axis.text.x = element_text(angle = 60, hjust=1))

KOSPI200_tilt = KOSPI200_tilt%>%
  mutate_at(vars(투자비중),list(~ifelse(차이 < -0.005, 시가총액비중 - 0.005, 투자비중)))%>%
  mutate_at(vars(투자비중),list(~ifelse(차이 >0.005, 시가총액비중 + 0.005, 투자비중)))%>%
  mutate(투자비중 = 투자비중/sum(투자비중),
             차이 = 투자비중 - 시가총액비중)
head(KOSPI200_tilt) #-->재표준화 과정에서 다시 차이가 50bp를 넘는 게 생김 --> 반복

while(max(abs(KOSPI200_tilt$차이))>(0.005+0.00001)){
  KOSPI200_tilt = KOSPI200_tilt%>%
    mutate_at(vars(투자비중),list(~ifelse(차이 < -0.005, 시가총액비중 - 0.005, 투자비중)))%>%
    mutate_at(vars(투자비중),list(~ifelse(차이 >0.005, 시가총액비중 + 0.005, 투자비중)))%>%
    mutate(투자비중 = 투자비중/sum(투자비중),
               차이 = 투자비중 - 시가총액비중)
}

head(KOSPI200_tilt)

KOSPI200_tilt %>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y=차이))+
  geom_point()+
  geom_hline(aes(yintercept = 0.005),color = 'red')+
  geom_hline(aes(yintercept = -0.005), color = 'red')+
  xlab('종목명')+
  ylab('비중차이(%)')+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by = 5),'종목명'])+
  scale_y_continuous(labels = scales::percent)+
  theme(axis.text.x = element_text(angle = 60, hjust = 1))

KOSPI200 %>%
  ggplot(aes(x=reorder(종목명,-시가총액비중),y = 시가총액비중))+
  geom_point()+
  geom_point(data = KOSPI200_tilt, aes(x=reorder(종목명,-시가총액비중),y=투자비중),
             color = 'red',shape = 4)+
  xlab('종목명')+
  ylab('비중(%)')+
  coord_cartesian(ylim = c(0,0.03))+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by = 5),'종목명'])+
  scale_y_continuous(labels = scales::percent)+
  theme(axis.text.x = element_text(angle = 60, hjust = 1))

KOSPI200_tilt_mod = KOSPI200_tilt%>%arrange(PBR)
KOSPI200_tilt_mod %>%
  ggplot(aes(x=reorder(종목명,PBR),y=차이))+
  geom_point()+
  geom_col(aes(x=reorder(종목명,PBR),y=PBR/2000),fill='blue',alpha = 0.2)+
  xlab('종목명')+
  ylab('차이(%)')+
  scale_y_continuous(labels = scales::percent,
                     sec.axis = sec_axis(~.* 2000,name = "PBR"))+
  scale_x_discrete(breaks = KOSPI200[seq(1,200,by=5),'종목명'])+
  theme(axis.text.x = element_text(angle = 60, hjust = 1))
  