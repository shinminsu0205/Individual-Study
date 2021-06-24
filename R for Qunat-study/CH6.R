#수정 주가 받아오기
library(stringr)
library(httr)
library(rvest)
library(lubridate)
library(stringr)
library(readr)
library(xts)
library(timetk)

KOR_ticker = read.csv('data/KOR_ticker.csv',row.names=1)
KOR_ticker$'종목코드' =
  str_pad(KOR_ticker$'종목코드',6,side = c("left"),pad='0')
print(KOR_ticker$'종목코드'[1])

ifelse(dir.exists('data/KOR_price'),FALSE,
       dir.create('data/KOR_price'))

for (i in 1:nrow(KOR_ticker)){
  
  name = KOR_ticker$'종목코드'[i]
  
  price = xts(NA, order.by = Sys.Date()) #빈 시계열 데이터 생성
  from = (Sys.Date() - years(3))%>% str_remove_all('-')
  to = Sys.Date() %>% str_remove_all('-')
  
  #오류 발생시 무시하고 다음 루프로 진행
  tryCatch({
    #url 생성
    url = paste0('https://fchart.stock.naver.com/siseJson.nhn?symbol=',name,
                 '&requestType=1&startTime=',from,'&endTime=',to,'&timeframe=day')
    data = GET(url)
    data_html = data%>% read_html %>%
      html_text()%>%
      read_csv()
    
    price = data_html[c(1,5)] #날짜와 종가 데이터만 선택
    colnames(price) = (c('Date','Price'))
    price = na.omit(price)
    price$Date = parse_number(price$Date) #불필요한 문자 제거 후 숫자형 데이터로 변경
    price$Date = ymd(price$Date) #yyyymmdd -> yyyy-mm-dd의 date타입으로 변경
    price = tk_xts(price, date_var = Date) #date열을 인덱스로 시계열 데이터 생성
  }, error = function(e) {
    #오류 발생시 해당 종목명을 출력하고 다음 루프로 이동
    warning(paste0("Error in ticker:",name))
  })
  
  #다운로드 받은 파일을 생성한 폴더 내 csv로 저장
  write.csv(data.frame(price),
            paste0('data/KOR_price/',name,'_price.csv'),
            fileEncoding='EUC-KR')
  Sys.sleep(2)
}

#재무 제표 및 가치지표 크롤링
ifelse(dir.exists('data/KOR_fs'),FALSE,
       dir.create('data/KOR_fs'))
Sys.setlocale("LC_ALL","English")

url = paste0('http://comp.fnguide.com/SVO2/ASP/',
'SVD_Finance.asp?pGB=1&gicode=A005930&cID=&MenuYn=Y&ReportGB=&NewMenuID=103&stkGb=701')

data = GET(url,
           user_agent('Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36'))

data = data %>%
  read_html() %>%
  html_table()

Sys.setlocale("LC_ALL","Korean")

lapply(data,function(x){
  head(x,3)
})

data_IS = data[[1]] #연간 손익 계산서
data_BS = data[[3]] #연간 재무 상태표
data_CF = data[[5]] #연간 현금 흐름표

print(names(data_IS))

data_IS = data_IS[, 1:(ncol(data_IS)-2)] #전년동기, 전년동기(%)열제거

data_fs = rbind(data_IS,data_BS,data_CF)
data_fs[,1] = sapply(data_fs[,1], function(x) 
  {gsub('계산에 참여한 계정 펼치기','',x)})
#data_fs$'IFRS(연결)' = gsub("계산에 참여한 계정 펼치기", "", data_fs$'IFRS(연결)')
#필요 없는 것 제거
#column에 gsub 활용할 때는 데이터 형태 변환을 막기 위해서 lapply활용해야함.
data_fs = data_fs[!duplicated(data_fs[,1]),]

rownames(data_fs) = NULL
data_fs = as.data.frame(data_fs, row.names = data_fs[,1])
rownames(data_fs) = data_fs[,1]

data_fs[,1] = NULL
data_fs = data_fs[,substr(colnames(data_fs),6,7)=='12'] #12월 결산 데이터만 사용하겠다.

data_fs = sapply(data_fs, function(x){
  str_replace_all(x,',','')%>%
    as.numeric()
})%>%
  data.frame(.,row.names=rownames(data_fs))
write.csv(data_fs, 'data/KOR_fs/005930_fs.csv',fileEncoding = 'EUC-KR')


#가치지표 계산하기
ifelse(dir.exists('data/KOR_value'),FALSE, dir.create('data/KOR_value'))
value_type = c('지배주주순이익',
              '자본',
              '영업활동으로인한현금흐름',
              '매출액')
value_index = data_fs[match(value_type, rownames(data_fs)),
                      ncol(data_fs)] #분모에 해당하는 항목을 저장한 후, match 함수를 통해 해당 항목 위치 확인
#ncol 함수를 이용해 가장 최근년도 재무제표 데이터를 선택
#print(value_index)
url = paste('http://comp.fnguide.com/SVO2/ASP/SVD_main.asp?pGB=1&gicode=A005930')
headers = c('User-Agent' = 'Mozilla/5.0')
data = GET(url,add_headers(.headers = headers))

price = read_html(data) %>%
  html_node(xpath='//*[@id="svdMainChartTxt11"]')%>%
  html_text()%>%
  parse_number()

share = read_html(data)%>%
  html_node(xpath = '//*[@id="svdMainGrid1"]/table/tbody/tr[7]/td[1]')%>%
  html_text()
share = share %>%
  strsplit('/')%>% #리스트 형태로 출력
  unlist()%>% #리스트를 벡터 형태로 변환
  .[1]%>% #첫 번째 데이터 선택
  parse_number()

data_value = price / (value_index * 100000000 / share) #주가는 원 단위이고, 재무 데이터는 억 단위이므로 맞춰줌.
names(data_value) = c('PER','PBR','PCR','PSR')
data_value[data_value < 0] = NA
write.csv(data_value, 'data/KOR_value/005930_value.csv',fileEncoding = 'EUC-KR')

##전 종목 재무제표 및 가치지표 다운로드
KOR_ticker = read.csv('data/KOR_ticker.csv',row.names = 1)
KOR_ticker$'종목코드' =
  str_pad(KOR_ticker$'종목코드',6,side=c('left'),pad='0')

ifelse(dir.exists('data/KOR_fs'),FALSE,dir.create('data/KOR_fs'))
ifelse(dir.exists('data/KOR_value'),FALSE,dir.create('data/KOR_value'))

for (i in 1:nrow(KOR_ticker)){
  
  data_fs = c()
  data_value = c()
  name = KOR_ticker$'종목코드'[i]
  
  #오류 발생 시 이를 무시하고 다음 루프로 진행
  tryCatch({
    Sys.setlocale('LC_ALL','English')
    
    #URL생성
    url = paste0('http://comp.fnguide.com/SVO2/ASP/',
                 'SVD_Finance.asp?pGB=1&gicode=A',name,
                 '&cID=&MenuYn=Y&ReportGB=&NewMenuID=103&stkGb=701')
    data = GET(url,
               user_agent('Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36'))%>%
      read_html()%>%
      html_table()
    Sys.setlocale('LC_ALL','Korean')
    
    data_IS = data[[1]]
    data_BS = data[[3]]
    data_CF = data[[5]]
    
    data_IS = data_IS[,1:(ncol(data_IS)-2)]
    data_fs = rbind(data_IS,data_BS,data_CF)
    data_fs[,1] = sapply(data_fs[,1], function(x) 
    {gsub('계산에 참여한 계정 펼치기','',x)})
    
    #데이터 클렌징
    data_fs = data_fs[!duplicated(data_fs[,1]),]
    data_fs = as.data.frame(data_fs, row.names = data_fs[,1])
    rownames(data_fs) = data_fs[,1]

    
    
    data_fs[,1] = NULL
    
    #12월 재무제표만 선택
    data_fs=
      data_fs[,substr(colnames(data_fs),6,7)=="12"]
    data_fs = sapply(data_fs, function(x){
      str_replace_all(x,',','')%>%
        as.numeric()
    })%>%
      data.frame(.,row.names=rownames(data_fs))
    
    #가치지표 분모
    value_type = c('지배주주순이익',
                   '자본',
                   '영업활동으로인한현금흐름',
                   '매출액')
    #해당 재무 데이터만 선택
    value_index = data_fs[match(value_type, rownames(data_fs)),
                          ncol(data_fs)]
    
    #Snapshot 페이지 불러오기
    url = paste0('http://comp.fnguide.com/SVO2/ASP/SVD_main.asp?pGB=1&gicode=A',name)
    headers = c('User-Agent' = 'Mozilla/5.0')
    data = GET(url,add_headers(.headers = headers))
    
    #현재 주가 크롤링
    price = read_html(data)%>%
      html_node(xpath = '//*[@id="svdMainChartTxt11"]')%>%
      html_text()%>%
      parse_number()
    
    #보통주 발행 주식 수 크롤링
    share = read_html(data)%>%
      html_node(xpath = '//*[@id="svdMainGrid1"]/table/tbody/tr[7]/td[1]')%>%
      html_text()%>%
      strsplit('/')%>%
      unlist()%>%
      .[1]%>%
      parse_number()
    
    #가치지표 계산
    data_value = price / (value_index * 100000000/ share)
    names(data_value) = c('PER','PBR','PCR','PSR')
    data_value[data_value < 0] = NA
  }, error = function(e){
    
    #오류 발생시 해당 종목명을 출력하고 다음 루프로 이동
    data_fs <<- NA
    data_value <<- NA
    warning(paste0("Error in Ticker: ",name))
  })
  
  #다운로드한 파일을 생성한 각 폴더 내 csv 파일로 저장
  #재무제표 저장
  write.csv(data_fs,paste0('data/KOR_fs/',name,'_fs.csv'),fileEncoding = 'EUC-KR')
  
  #가치지표 저장
  write.csv(data_value,paste0('data/KOR_value/',name,'_value.csv'),fileEncoding = 'EUC-KR')
  
  Sys.sleep(2)
}
