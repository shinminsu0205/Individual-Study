library(stringr)

KOR_ticker = read.csv('data/KOR_ticker.csv',row.names = 1, stringsAsFactors = FALSE)
KOR_sector = read.csv('data/KOR_sector.csv',row.names = 1, stringsAsFactors = FALSE)

KOR_ticker$종목코드 = str_pad(KOR_ticker$종목코드,6,side = c(left),0)
KOR_sector$CMP_CD = str_pad(KOR_sector$CMP_CD,6,side = c(left),0)

#두 테이블 합치기(Using dplyr)
library(dplyr)
data_market = left_join(KOR_ticker, KOR_sector, 
                        by = c('종목코드' = 'CMP_CD',
                               '종목명' = 'CMP_KOR'))
#데이터 구조 확인하기 glimpse()
glimpse(data_market)

#rename: 열 이름 바꾸기
data_market = data_market %>%
  rename('배당수익률(%)' = '배당수익률')

#distinct(): 고유값 확인하기
data_market %>%
  distinct(SEC_NM_KOR) %>% c()

#select():원하는 열만 선택
data_market %>%
  select('종목명') %>% head()
data_market %>%
  select('종목명','PBR','SEC_NM_KOR') %>% head()
data_market %>%
  select(starts_with('시')) %>% head()
data_market %>%
  select(ends_with('R')) %>% head()
data_market %>%
  select(contains('가'))%>%head()

#mutate(): 열 생성 및 데이터 변형
data_market = data_market %>%
  mutate('PBR' = as.numeric(PBR),
         'PER' = as.numeric(PER),
         'ROE' = PBR/PER,
         'ROE' = round(ROE,4),
         'size' = ifelse('시가총액' >=
                           median('시가총액',na.rm = TRUE),'big','small'))
data_market %>%
  select('종목명','ROE','size')%>%head()

#filter():조건을 충족하는 행 선택
data_market %>%
  select('종목명','PBR') %>%
  filter(PBR < 1) %>% head()

data_market %>%
  select('종목명','PBR','PER','ROE') %>%
  filter(PBR < 1 & PER < 20 & ROE >0.1) %>% head()

#summarize():요약 통곗값 계산
data_market %>%
  summarize(PBR_max = max(PBR, na.rm = TRUE),
            PBR_min = min(PBR, na.rm = TRUE))

#arrange(): 데이터 정렬
data_market %>%
  select(PBR) %>%
  arrange(PBR) %>%
  head(5)

data_market %>%
  select(ROE)%>%
  arrange(desc(ROE))%>%
  head(5)

#row_number(): 순위 계산
data_market %>%
  mutate(PBR_rank = row_number(PBR))%>%
  select('종목명', PBR, PBR_rank)%>%
  arrange(PBR)%>%
  head(5)

data_market %>%
  mutate(PBR_rank = row_number(desc(ROE))) %>%
  select('종목명',ROE,PBR_rank)%>%
  arrange(desc(ROE)) %>%
  head(5)

#ntile():분위수 계산
data_market %>%
  mutate(PBR_tile = ntile(PBR,n=5))%>%
  select(PBR, PBR_tile)%>%
  head()

#group_by():그룹별로 데이터 묶기
data_market %>%
  group_by(SEC_NM_KOR) %>%
  summarize(n()) #n() : 그룹 내 데이터 개수 확인

data_market %>%
  group_by(SEC_NM_KOR)%>%
  summarize(PBR_median = median(PBR,na.rm =TRUE)) %>%
  arrange(PBR_median)

data_market %>%
  group_by(시장구분, SEC_NM_KOR) %>%
  summarize(PBR_median = median(PBR,na.rm=TRUE))%>%
  arrange(PBR_median)

##ggplot 기초
#diamonds dataset
#1.data:시각화에 사용될 데이터
#2.aes:데이터를 나타내는 시각적 요소(x,y축, 사이즈, 색깔 등)
#3.geom: 데이터를 나타내는 도형
#4.Facets: 하위 집합으로 분할하여 시각화
#5.Statistics: 통곗값
#6.Coordinates:데이터를 표현할 좌표계
#7.Theme: 그래프를 꾸밈
library(ggplot2)
data(diamonds)
head(diamonds)
ggplot(data=diamonds,aes(x=carat, y=price))+
  geom_point()

#data 파이프라인을 통한 연결
library(magrittr)
diamonds %>%
  ggplot(aes(x=carat,y=price)) + 
  geom_point(aes(color = cut)) #aes()를 통해 점의 색깔을 매핑
  #color = cut: cut에 따라 점의 색깔을 다르게 표현

#facets:하위 집합으로 나누어 시각화
diamonds %>%
  ggplot(aes(x=carat, y =price))+
  geom_point()+
  facet_grid(.~cut) #~:하위집합으로 나누고자 하는 변수

#statistics
diamonds %>%
  ggplot(aes(x=cut, y= carat))+
  stat_summary_bin(fun = 'mean',geom='bar')
  #cut에 따른 carat의 평균값을 나타내고 싶을 때

#coordinates
diamonds %>%
  ggplot(aes(x=carat,y=price))+
  geom_point(aes(color = cut))+
  coord_cartesian(xlim = c(0,3), ylim = c(0,20000))
  #coord_cartesian을 통해서 x축 y축 한계 설정 가능.

diamonds %>%
  ggplot(aes(x=carat,y=price))+
  geom_boxplot(aes(group = cut))+
  coord_flip() #x축과 y축을 뒤집어서 표현

#theme
diamonds %>%
  ggplot(aes(x = carat, y =price)) +
  geom_point(aes(color = cut)) +
  theme_bw() + ##뒷 배경을 하얀색으로 지정
  labs(title = 'Relation btw Carat & Price',
       x = 'Carat', y = 'Price')+ ##x,y축, 제목 설정
  theme(legend.position = 'bottom',
        panel.grid.major.x = element_blank(),
        panel.grid.minor.x = element_blank(),
        panel.grid.major.y = element_blank(),
        panel.grid.minor.y = element_blank())+ # 격자제거
  scale_y_continuous(
    labels = function(x){
      paste0('$',format(x,big.mark = ',')) #천원 단위로 , 를 찍고 $와 결합.
    }
  )

##종목정보 시각화
library(ggplot2)
ggplot(data_market,aes(x=ROE,y=PBR))+geom_point()

ggplot(data_market,aes(x=ROE,y=PBR))+
  geom_point() +
  coord_cartesian(xlim = c(0,0.4),ylim = c(0,3))

ggplot(data_market,aes(x=ROE,y=PBR, color = 시장구분,
                       shape = 시장구분))+
  geom_point()+
  geom_smooth(method = 'lm')+
  coord_cartesian(xlim=c(0,0.3),ylim = c(0,3))

#geom_histogram()
ggplot(data_market, aes(x=PBR))+
  geom_histogram(binwidth = 0.1)+
  coord_cartesian(xlim = c(0,10))

ggplot(data_market, aes(x=PBR))+
  geom_histogram(aes(y = ..density..), #density function으로 전환
                 binwidth = 0.1,
                 color = 'skyblue', fill = 'sky blue')+
  coord_cartesian(xlim=c(0,10))+
  geom_density(color = 'red')+ #density line으로 전환
  geom_vline(aes(xintercept = median(PBR, na.rm=TRUE)),
             color = 'blue')+ #geom_vline을 통해 세로선을 그어주는데, xintercept(x축)로 PBR의 중앙값을 선택
  geom_text(aes(label = median(PBR,na.rm = TRUE),
                x=median(PBR, na.rm = TRUE), y =0.05), #geom_text를 통해 텍스트를 삽입하는데 넣을 값을 median으로 x축 값의 median으로 잡아준 것.y=0.05는 y축 위치임.
            col='black',size = 6, hjust = -0.5)

##geom_boxplot():박스 플롯 나타내기
ggplot(data_market, aes(x = SEC_NM_KOR,y=PBR))+
  geom_boxplot()+
  coord_flip()

##dplyr과 ggplot을 연결해 사용해보기
data_market%>%
  filter(!is.na(SEC_NM_KOR))%>%
  group_by(SEC_NM_KOR) %>%
  summarize(ROE_sector = median(ROE,na.rm = TRUE),
            PBR_sector = median(PBR, na.rm=TRUE)) %>%
  ggplot(aes(x=ROE_sector, y=PBR_sector,
             color = SEC_NM_KOR, label = SEC_NM_KOR))+
  geom_point()+
  geom_text(color = 'black',size=3,vjust=1.3)+
  theme(legend.position = 'bottom',
        legend.title= element_blank())

#geom_bar():막대 그래프
data_market%>%
  group_by(SEC_NM_KOR)%>%
  summarize(n=n())%>%
  ggplot(aes(x=SEC_NM_KOR,y=n))+
  geom_bar(stat = 'identity')+ #y축에 n을 그대로 사용하기 위해서 stat = 'identity'로 지정
  theme_classic()
#막대 그래프 크기순 정렬
data_market %>%
  filter(!is.na(SEC_NM_KOR))%>%
  group_by(SEC_NM_KOR)%>%
  summarize(n=n())%>%
  ggplot(aes(x=reorder(SEC_NM_KOR,n),y=n,label=n))+
  #reorder 함수를 통해 SEC_NM_KOR을 n을 기준으로 정렬
  geom_bar(stat='identity')+
  geom_text(color = 'black',size = 4, hjust = -0.3)+
  xlab(NULL)+
  ylab(NULL)+
  coord_flip()+
  scale_y_continuous(expand = c(0,0,0.1,0))+
  theme_classic()

##주가 및 수익률 시각화
#주가 그래프 나타내기
library(quantmod)
getSymbols('SPY')
prices = Cl(SPY) #Cl : closed price만 가져옴.
plot(prices, main = 'Price')

library(ggplot2)

SPY %>%
  ggplot(aes(x=Index, y=SPY.Close))+
  geom_line()

#인터랙티브 그래프 나타내기
library(dygraphs)
dygraph(prices)%>%
  dyRangeSelector()

library(highcharter)
highchart(type = 'stock')%>%
  hc_add_series(prices)%>%
  hc_scrollbar(enabled=FALSE)

library(plotly)
p = SPY %>%
  ggplot(aes(x=Index,y=SPY.Close))+
  geom_line()

ggplotly(p)

prices%>%
  fortify.zoo %>%
  plot_ly(x=~Index,y=~SPY.Close)%>%# 함수 내부에 x축, y축 설정/ 변수명 앞에 ~을 붙임.
  add_lines()

##연도별 수익률 나타내기
library(PerformanceAnalytics)

ret_yearly = prices %>%
  Return.calculate()%>%
  apply.yearly(.,Return.cumulative)%>% #연도별 수익률 계산후 반올림.
  round(4)%>%
  fortify.zoo()%>% #인덱스에 있는 시간 데이터를 Index 열로 이동
  mutate(Index = as.numeric(substring(Index,1,4))) #Index 열의 1~4번째 글자를 추출한 후 숫자형으로 저장
ggplot(ret_yearly,aes(x=Index,y=SPY.Close))+
  geom_bar(stat = 'identity')+
  scale_x_continuous(breaks = ret_yearly$Index,
                     expand = c(0.01,0.01))+ #x축에 모든 연도가 표현되도록 설정
  geom_text(aes(label = paste(round(SPY.Close * 100,2),"%"),
                vjust = ifelse(SPY.Close >= 0,-0.5,1.5)), #vjust 내의 ifelse 함수를 활용해서 수익률이 0보다 크면 위쪽에 표시하고 아니면 아래쪽에 표시하도록 함.
            position = position_dodge(width = 1),
            size = 3)+
  xlab(NULL)+ylab(NULL)

##fortify.zoo 보충 설명: zoo형태의 데이터(시계열 데이터)를 dataframe으로 바꿈.