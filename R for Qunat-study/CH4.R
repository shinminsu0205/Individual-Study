#get method crawling

library(rvest)
library(httr)

url = 'https://finance.naver.com/news/news_list.nhn?mode=LSS2D&section_id=101&section_id2=258'
data = GET(url)

print(data)

data_title = data %>%
  read_html(encoding = 'EUC-KR') %>%
  html_nodes('dl') %>%
  html_nodes('.articleSubject') %>%
  html_nodes('a') %>%
  html_attr('title')
print(data_title)

#post 방식 웹 크롤링
library(httr)
library(rvest)

Sys.setlocale("LC_ALL","English") #한글로 작성된 페이지 크롤링 오류 방지를 위해서 locale 언어를 영어로 설정

url = "https://kind.krx.co.kr/disclosure/todaydisclosure.do"
data = POST(url, body = 
              list(method= 'searchTodayDisclosureSub',
                   currentPageSize= '15',
                   pageIndex= '1',
                   orderMode= '0',
                   orderStat= 'D',
                     forward= 'todaydisclosure_sub',
                     chose= 'S',
                   todayFlag= 'Y',
                   selDate= '2021-03-15'
              ))

data = read_html(data) %>%
  html_table(fill=TRUE)%>% #셀 병합이 된 열 때문에 fill = True
  .[[1]] #첫 번째 리스트 선택
Sys.setlocale("LC_ALL","Korean")
print(head(data))

#ticker crawling via naver finance
library(httr)
library(rvest)

i = 0
ticker = list()
url = paste0('https://finance.naver.com/sise/','sise_market_sum.nhn?sosok=',i,'&page=1')
down_table = GET(url)
navi.final = read_html(down_table, encoding = 'EUC-KR') %>%
  html_nodes(.,'.pgRR') %>% #클래스 속성이니까 앞에 마침표
  html_nodes(.,'a') %>% #a태그 정보만
  html_attr(.,'href') #href 속성
print(navi.final)

navi.final = navi.final %>%
  strsplit(.,'=') %>% #=을 기준으로 문장을 나눔
  unlist() %>% #리스트 형태에서 벡터 형태로 전환
  tail(.,1) %>% #뒤에서 첫 번째 데이터만 선택
  as.numeric()
print(navi.final)

i=0 #코스피
j=1 #첫 번째 페이지
url = paste0('https://finance.naver.com/sise/','sise_market_sum.nhn?sosok=',i,'&page=',j)
down_table = GET(url)
Sys.setlocale("LC_ALL","English")
table = read_html(down_table, encoding = 'EUC-KR') %>%
  html_table(fill=TRUE)
table = table[[2]] #우리에게 필요한 테이블 변수는 두 번째 것.
Sys.setlocae("LC_ALL","Korean")
print(head(table))

table[,ncol(table)] = NULL
table = na.omit(table)
print(head(table))

symbol = read_html(down_table, encoding = 'EUC-KR') %>%
  html_nodes(.,'tbody') %>%
  html_nodes(.,'td') %>%
  html_nodes(.,'a') %>%
  html_attr(.,'href')
print(head(symbol,10))

symbol = sapply(symbol, function(x){
  substr(x, nchar(x) - 5, nchar(x)) #마지막 여섯글자만 추출
})
print(head(symbol, 10))
symbol = unique(symbol) #symbol이 두 번 들어가서 중복돼서 나오니 하나만 받게 함.
print(head(symbol,10))

table$N = symbol
colnames(table[1]) = '종목코드'
rownames(table) = NULL
ticker[[j]] = table

#정리된 버전
data = list()

#i = 0은 코스피, 1은 코스닥

for (i in 0:1){
  
  ticker = list()
  url = paste0('https://finance.naver.com/sise/','sise_market_sum.nhn?sosok=',i,'&page=1')
  down_table = GET(url)
  
  #최종 페이지 번호
  navi.final = read_html(down_table, encoding = 'EUC-KR') %>%
    html_nodes(.,".pgRR")%>%
    html_nodes(.,"a") %>%
    html_attr(.,'href')%>%
    strsplit(.,"=")%>%
    unlist()%>%
    tail(.,1)%>%
    as.numeric()
  
  #첫번째부터 마지막 페이지까지 for를 활용해서 추출
  for (j in 1:navi.final){
    
    #각 페이지에 해당하는 URL 생성
    url = paste0('https://finance.naver.com/sise/','sise_market_sum.nhn?sosok=',i,'&page=',j)
    down_table = GET(url)
    Sys.setlocale("LC_ALL","English")
    table = read_html(down_table, encoding = "EUC-KR") %>%
      html_table(fill=TRUE)
    table = table[[2]]
    Sys.setlocale("LC_ALL","Korean")
    
    table[,ncol(table)] = NULL
    table = na.omit(table)
    
    #6자리 티커 추출
    symbol = read_html(down_table, encoding = "EUC-KR")%>%
      html_nodes(.,"tbody")%>%
      html_nodes(.,"td")%>%
      html_nodes(.,"a")%>%
      html_attr(.,"href")
    
    symbol = sapply(symbol, function(x){
      substr(x, nchar(x)-5, nchar(x))
    })%>% unique()
    
    #테이블에 티커를 넣어준 후 정리
    table$N = symbol
    colnames(table)[1] = "종목코드"
    
    rownames(table) = NULL
    ticker[[j]] = table
    
    Sys.sleep(1) #페이지당 슬립 적용
  }
  ticker = do.call(rbind, ticker) #do.call을 통해 리스트를 데이터 프레임으로 묶기
  data[[i+1]] = ticker
}

data = do.call(rbind, data)