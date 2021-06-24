library(httr)
library(rvest)
library(readr)
library(stringr)

#날짜 크롤링

url = 'https://finance.naver.com/sise/sise_deposit.nhn'

biz_day = GET(url)%>%
  read_html(encoding = 'EUC-KR')%>%
  html_nodes(xpath=
               '//*[@id="type_0"]/div/ul[2]/li/span')%>%
  html_text()%>%
  str_match(('[0-9]+.[0-9]+.[0-9]+'))%>%
  str_replace_all('\\.','')

#코스피(섹터별) 받아오기

gen_otp_url = 'http://data.krx.co.kr/comm/fileDn/GenerateOTP/generate.cmd'
gen_otp_data = list(
  mktId= 'STK',
  trdDd= biz_day,
  money= '1',
  csvxls_isNo= 'false',
  name= 'fileDown',
  url= 'dbms/MDC/STAT/standard/MDCSTAT03901'
)

otp = POST(gen_otp_url,query = gen_otp_data) %>%
  read_html() %>%
  html_text()

down_url = 'http://data.krx.co.kr/comm/fileDn/download_csv/download.cmd'
down_sector_KS = POST(down_url, query = list(code=otp),
                      add_headers(referer = gen_otp_url)) %>%
  read_html(encoding = 'EUC-KR')%>%
  html_text()%>%
  read_csv
print(down_sector_KS)

#코스닥 받아오기
gen_otp_data = list(
  mktId= 'KSQ',
  trdDd= biz_day,
  money= '1',
  csvxls_isNo= 'false',
  name= 'fileDown',
  url= 'dbms/MDC/STAT/standard/MDCSTAT03901'
)

otp = POST(gen_otp_url, query = gen_otp_data)%>%
  read_html() %>%
  html_text()

down_sector_KQ = POST(down_url, query = list(code = otp),
                      add_headers(referer = gen_otp_url)) %>%
  read_html(encoding = 'EUC-KR')%>%
  html_text()%>%
  read_csv()

down_sector = rbind(down_sector_KS, down_sector_KQ)

#데이터 파일 저장
ifelse(dir.exists('data'), FALSE, dir.create('data'))
write.csv(down_sector, 'data/krx_sector.csv',fileEncoding = 'EUC-KR')

#개별종목 지표 크롤링

gen_otp_url = 
  'http://data.krx.co.kr/comm/fileDn/GenerateOTP/generate.cmd'
gen_otp_data = list(
  searchType= '1',
  mktId= 'ALL',
  trdDd= biz_day,
  csvxls_isNo= 'false',
  name= 'fileDown',
  url= 'dbms/MDC/STAT/standard/MDCSTAT03501'
)
otp = POST(gen_otp_url, query = gen_otp_data)%>%
  read_html()%>%
  html_text()

down_url = 'http://data.krx.co.kr/comm/fileDn/download_csv/download.cmd'
down_ind = POST(down_url, query = list(code = otp),
                add_headers(referer = gen_otp_url)) %>%
  read_html(encoding = 'EUC-KR')%>%
  html_text()%>%
  read_csv()
print(down_ind)
write.csv(down_ind, 'data/krx_ind.csv', fileEncoding='EUC-KR')

#거래소 데이터 정리
down_sector = read.csv('data/krx_sector.csv',row.names=1,
                       stringsAsFactors = FALSE)
down_ind = read.csv('data/krx_ind.csv',row.names=1,
                    stringsAsFactors = FALSE)
intersect(names(down_sector), names(down_ind)) #중복되는 칼럼 확인
setdiff(down_sector[,'종목명'],down_ind[,'종목명']) #둘 중 하나라도 없는 종목
#보통 둘 중 하나라도 없는 종목은 선박, 광물, 해외 종목 등 일반적이지 않은 종목들임.

KOR_ticker = merge(down_sector, down_ind,
                   by = intersect(names(down_sector),
                                  names(down_ind)),
                   all=FALSE) #all =FALSE:교집합 반환(True이면 합집합 반환)
KOR_ticker = KOR_ticker[order(-KOR_ticker['시가총액']),]
#order(-'~~~'):내림차순 정렬 --> 시가총액 기준으로 내림차순 정렬
KOR_ticker[grepl('스팩',KOR_ticker[,'종목명']),'종목명']
#스팩이 들어간 종목 확인
KOR_ticker[str_sub(KOR_ticker[,'종목코드'],-1,-1) != 0, '종목명']
#우선주 종목 확인 < 우선주는 종목코드 끝자리가 0이 아니다.
#str_sub(데이터셋, 찾고자 하는 문자열의 시작위치, 찾고자 하는 문자열의 끝위치)

KOR_ticker = KOR_ticker[!grepl('스팩',KOR_ticker[,'종목명']),]
KOR_ticker = KOR_ticker[str_sub(KOR_ticker[,'종목코드'],-1,-1) == 0,]

rownames(KOR_ticker) = NULL
write.csv(KOR_ticker,'data/KOR_ticker.csv',fileEncoding = 'EUC-KR')

print(head(KOR_ticker))

#WICS 기준 섹터 정보 크롤링
library(jsonlite) #WICS 섹터 정보가 JSON으로 작성돼있음
url=paste0('http://www.wiseindex.com/Index/GetIndexComponets',
           '?ceil_yn=0&dt=20210326&sec_cd=G10')
data = fromJSON(url)
lapply(data, head) #apply a function to list or vector

sector_code = c('G25','G35','G50','G40','G10','G20','G55',
                'G30','G15','G45')
data_sector = list()
for (i in sector_code){
  url = paste0('http://www.wiseindex.com/Index/GetIndexComponets',
               '?ceil_yn=0&dt=20210326&sec_cd=',i)
  data = fromJSON(url)
  data = data$list
  
  data_sector[[i]]=data
  
  Sys.sleep(1)
}
data_sector = do.call(rbind, data_sector)
write.csv(data_sector,'data/KOR_sector.csv',fileEncoding = 'EUC-KR')
