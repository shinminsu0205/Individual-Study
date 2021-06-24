setwd("C:\\Users\\kyle0\\Desktop\\Git\\Individual-Study\\R for Qunat-study")
library(dplyr)
library(readxl)
library(xts)
library(timetk)

url = "https://images.aqr.com/-/media/AQR/Documents/Insights/Data-Sets/Quality-Minus-Junk-Factors-Monthly.xlsx"
tf = tempfile(fileext = '.xlsx')
download.file(url,tf,mode = 'wb')
excel_sheets(tf) #시트명 확인
df_QMJ = read_xlsx(tf, sheet = 'QMJ Factors',skip = 18)%>%
  select(DATE,Global)
df_MKT = read_xlsx(tf, sheet = 'MKT',skip = 18)%>%
  select(DATE, Global)
df_SMB = read_xlsx(tf, sheet = 'SMB',skip = 18)%>%
  select(DATE, Global)
df_HML_Devil = read_xlsx(tf,sheet = 'HML Devil', skip = 18)%>%
  select(DATE, Global)
df_UMD = read_xlsx(tf, sheet = 'UMD', skip =18)%>%
  select(DATE,Global)
df_RF = read_xlsx(tf, sheet = 'RF', skip = 18) #18행까지는 각 데이터를 설명하는 텍스트이므로 제외

df = Reduce(function(x,y) inner_join(x,y, by = 'DATE'), #inner_join함수가 최대 두 개밖에 선택을 못 하므로 Reduce함수를 사용해서 모든 테이블을 선택해서 합칠 수 있도록 만듦.
            list(df_QMJ,df_MKT,df_SMB,df_HML_Devil,df_UMD,df_RF))%>%
  setNames(c('DATE','QMJ','MKT','SMB','HML','UMD','RF'))%>%
  na.omit()%>%
  mutate(DATE = as.Date(DATE,"%m/%d/%Y"),
         R_excess = QMJ-RF,
         Mkt_excess = MKT-RF)%>%
  tk_xts(date_var = DATE) #티블 형태 데이터를 시계열 형태로 변경, 인덱스는 DATE 열

# 결과 측정 지표
##수익률 및 변동성
library(PerformanceAnalytics)
chart.CumReturns(df$QMJ)
prod((1+df$QMJ))-1 #누적 수익률
mean(df$QMJ) * 12 #연율화 수익률(산술) = mean of return * scale
(prod((1+df$QMJ)))^(12/nrow(df$QMJ)) -1 #연율화 수익률(기하) = product of (1+returns)^(scale/days)-1, where 'days' means the observation period

Return.cumulative(df$QMJ)
Return.annualized(df$QMJ, geometric = FALSE)
Return.annualized(df$QMJ,geometric = TRUE)

sd(df$QMJ)*sqrt(12) #연율화 변동성
StdDev.annualized(df$QMJ) #연율화 변동성
SharpeRatio.annualized(df$QMJ,Rf = df$RF, geometric = TRUE)

##낙폭과 최대낙폭
table.Drawdowns(df$QMJ)
maxDrawdown(df$QMJ)
chart.Drawdown(df$QMJ)

##CalmarRatio: 연율화수익률/최대낙폭 --> 절대 안전 투자를 추구하는 헤지펀드에서 자주 활용
CalmarRatio(df$QMJ)

##연도별 수익률
apply.yearly(df$QMJ,Return.cumulative)%>%head()

library(lubridate)
library(tidyr)
library(ggplot2)

R.yr = apply.yearly(df$QMJ,Return.cumulative)%>%
  fortify.zoo()%>%
  mutate(Index = year(Index))%>%
  gather(key,value,-Index)%>% #여러칼럼을 하나의 칼럼으로 변형 gather(key,value,이후 하나로 합치고자 하는 칼럼들)로 활용한다. key, value는 관용적으로 그냥 key, value를 그대로 적어주면 된다.
  mutate(key = factor(key,levels=unique(key))) #key에서 중복을 제거합니다.

ggplot(R.yr,aes(x=Index,y=value,fill = key))+
  geom_bar(position = "dodge",stat="identity")+
  ggtitle('Yearly Return')+
  xlab(NULL)+
  ylab(NULL)+
  theme_bw()+
  scale_y_continuous(expand=c(0.03,0.03))+
  scale_x_continuous(breaks = R.yr$Index,
                     expand = c(0.01,0.01))+
  theme(plot.title = element_text(hjust = 0.5,size = 12),
        legend.position = 'bottom',
        legend.title = element_blank(),
        legend.text = element_text(size = 7),
        axis.text.x = element_text(angle=45,hjust=1,size = 8),
        panel.grid.minor.x = element_blank())+
  guides(fill = guide_legend(byrow = TRUE))+
  geom_text(aes(label = paste(round(value*100,2),"%"),
                vjust = 이상치(value>=0,-0.5,1.5)),
            position = position_dodge(width = 1),
            size = 3)

##승률 및 롤링 윈도우값
  ##승률 : (포트폴리오 수익률 > 벤치마크)일 수/전체기간
  ##벤치마크는 S&P500, KOSPI200과 같은 지수이기도 하지만 헤지펀드의 경우 0 또는 무위험수익률이기도 함.
UpsideFrequency(df$QMJ,MAR = 0)

##롤링 윈도우: 무작위 시점에 투자했을 때 향후 n개월 후 승률 혹은 연율화 수익률
roll_12 = df$QMJ %>% apply.monthly(.,Return.cumulative)%>%
  rollapply(.,12,Return.annualized)%>%na.omit()%>%
  UpsideFrequency()

roll_24 = df$QMJ%>%apply.monthly(.,Return.cumulative)%>%
  rollapply(.,24,Return.annualized)%>%na.omit()%>%
  UpsideFrequency()

roll_36 = df$QMJ%>%apply.monthly(.,Return.cumulative)%>%
  rollapply(.,36,Return.annualized)%>%na.omit()%>%
  UpsideFrequency()

roll_win = cbind(roll_12,roll_24,roll_36)
print(roll_win)

df$QMJ %>% apply.monthly(.,Return.cumulative)%>%
  rollapply(.,12,Return.annualized)%>%na.omit()%>%
  fortify.zoo()%>%
  ggplot(aes(x=Index,y=QMJ))+
  geom_line()+
  geom_hline(aes(yintercept = 0),color = 'red')+
  xlab(NULL)+ylab(NULL)

#팩터 회귀분석 및 테이블로 나타내기
reg = lm(R_excess ~ Mkt_excess + SMB + HML + UMD, data = df)
#summary(reg)
summary(reg)$coefficient

library(broom)
tidy(reg)

library(stargazer)
stargazer(reg,type='text',out='data/reg_table.html')