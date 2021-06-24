setwd("C:\\Users\\kyle0\\Desktop\\Git\\Individual-Study\\R for Qunat-study")
file.edit("~/.Renviron") ##R환경에 직접 편집

dart_api = Sys.getenv("dart_api_key")

library(httr)
library(rvest)
library(tidyverse)
library(xml2)

codezip_url = paste0("https://opendart.fss.or.kr/api/corpCode.xml?crtfc_key=",dart_api)

codezip_data = GET(codezip_url)

codezip_data$headers[["content-disposition"]]
tf = tempfile(fileext = '.zip') #create empty zip file

#writeBin: Save Binary file type, through content() we can save attached file's content as a type of raw.
writeBin(
  content(codezip_data, as="raw"),
  file.path(tf) #name of file
)

nm = unzip(tf,list = TRUE) #zip내의 파일 리스트 확인
print(nm)

code_data = read_xml(unzip(tf, nm$Name))
print(code_data)
##code_data는 html 형식으로 구성
#corp_code:고유번호
#corp_name:종목명
#corp_stock: 거래소 상장 티커

corp_code = code_data%>%html_nodes('corp_code')%>%html_text()
corp_name = code_data%>%html_nodes('corp_name')%>%html_text()
corp_stock = code_data%>%html_nodes('stock_code')%>%html_text()

corp_list = data.frame(
  'code' = corp_code,
  'name' = corp_name,
  'stock'=corp_stock,
  stringsAsFactors = FALSE
)
nrow(corp_list)
head(corp_list)

corp_list = corp_list[corp_list$stock !=" ",]
write.csv(corp_list,'data/corp_list.csv',fileEncoding = 'EUC-KR')

##공시 검색
#전체 공시 검색
library(lubridate)
library(stringr)
library(jsonlite)

bgn_date = (Sys.Date() - days(7)) %>% str_remove_all('-')
end_date = (Sys.Date() ) %>% str_remove_all('-')
notice_url = paste0('https://opendart.fss.or.kr/api/list.json?crtfc_key=',dart_api,'&bgn_de=',bgn_date,'&end_de=',end_date,'&page_no=1&page_count=100')
notice_data = fromJSON(notice_url)
notice_data = notice_data[['list']]

#특정 기업의 공시 검색
bgn_date = (Sys.Date() - days(30))%>%str_remove_all('-')
end_date = (Sys.Date())%>%str_remove_all('-')
corp_code = '00126380'

notice_url_ss = paste0('https://opendart.fss.or.kr/api/list.json?crtfc_key=',dart_api,'&corp_code=',corp_code,'&bgn_de=',bgn_date,'&end_de=',end_date,'&page_no=1&page_count=100')
notice_data_ss = fromJSON(notice_url_ss)
notice_data_ss = notice_data_ss[['list']]

notice_url_exam = notice_data_ss[1,'rcept_no']
notice_dart_url = paste0('http://dart.fss.or.kr/dsaf001/main.do?rcpNo=',notice_url_exam)

#사업보고서 주요 정보 획득(배당)
corp_code = '00126380'
bsns_year = '2019'
reprt_code = '11011'
url_div = paste0('https://opendart.fss.or.kr/api/alotMatter.json?crtfc_key=',dart_api,
'&corp_code=',corp_code,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code)
div_data_ss = fromJSON(url_div)
div_data_ss = div_data_ss[['list']]

#상장기업 재무정보
corp_code = '00126380'
bsns_year = '2019'
reprt_code = '11011'

url_single = paste0('https://opendart.fss.or.kr/api/fnlttSinglAcnt.json?crtfc_key=',dart_api,
'&corp_code=',corp_code,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code)
fs_data_single = fromJSON(url_single)
fs_data_single = fs_data_single[['list']]

##다중 재무정보 받기
corp_code = c('00126380','00413046','00190321')
bsns_year = '2019'
reprt_code = '11011'

url_multiple = paste0('https://opendart.fss.or.kr/api/fnlttMultiAcnt.json?crtfc_key=',dart_api,
'&corp_code=',corp_code,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code)
fs_data_multiple = fromJSON(url_multiple)
fs_data_multiple = fs_data_multiple[['list']]

fs_data_list = fs_data_multiple %>% split(f = .$corp_code)
lapply(fs_data_list,head,2)

##단일 회사 전체 재무제표
corp_code = '00126380'
bsns_year = '2019'
reprt_code = '11011'

url_fs_all = paste0(
  'https://opendart.fss.or.kr/api/fnlttSinglAcntAll.json?crtfc_key=',dart_api,
  '&corp_code=',corp_code,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code,
  '&fs_div=CFS'
)

fs_data_all = fromJSON(url_fs_all)
fs_data_all = fs_data_all[['list']]
yr_count = str_detect(colnames(fs_data_all),'trm_amount') %>% sum() ##trm_amount가 들어간 colnames의 갯수 확인
yr_name = seq(bsns_year,(bsns_year - yr_count + 1)) #열 이름에 들어갈 연도 생성

fs_data_all = fs_data_all[,c('corp_code','sj_nm','account_nm','account_detail')]%>%
  cbind(fs_data_all[,str_which(colnames(fs_data_all),'trm_amount')]) ##corp_code, sj_nm, account_nm, account_detail 및 연도별 금액에 해당하는 trm_amount가 포함된 열을 선택하고 합칩니다.
colnames(fs_data_all)[str_which(colnames(fs_data_all),'amount')] = yr_name
#연도별 데이터에 해당하는 열의 이름을 yr_name, 즉 각 연도로 변경.

##전체종목 재무제표 다운로드
library(stringr)

KOR_ticker = read.csv('data/KOR_ticker.csv',row.names = 1)
corp_list = read.csv('data/corp_list.csv',row.names = 1)

KOR_ticker$'종목코드' = 
  str_pad(KOR_ticker$'종목코드',6,side = c('left'),pad = '0') #str_pad함수를 통해서 코드를 여섯자리로 통일

corp_list$'code' = 
  str_pad(corp_list$'code',8,side = c('left'),pad='0')

corp_list$'stock' = 
  str_pad(corp_list$'stock',6,side = c('left'),pad = '0')

ticker_list = KOR_ticker %>% left_join(corp_list,by=c('종목코드' = 'stock'))%>%
  select('종목코드','종목명','code')

ifelse(dir.exists('data/dart_fs'),FALSE, dir.create('data/dart_fs'))

bsns_year = '2019'
reprt_code = '11011'

for(i in 1:nrow(ticker_list)){
  data_fs = c()
  name = ticker_list$code[i]
  
  #오류 발생 시 무시하고 진행
  
  tryCatch({
    #url 생성
    url = paste0('https://opendart.fss.or.kr/api/fnlttSinglAcntAll.json?crtfc_key=',dart_api,
                 '&corp_code=',name,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code,
                 '&fs_div=CFS')
    fs_data_all = fromJSON(url)
    fs_data_all = fs_data_all[['list']]
    
    #연결재무제표 없어서 NULL 반환 시
    #reprt_code를 OFS, 즉 재무제표 다운롣,
    if(is.null(fs_data_all)){
      url = paste0('https://opendart.fss.or.kr/api/fnlttSinglAcntAll.json?crtfc_key=',dart_api,
                   '&corp_code=',name,'&bsns_year=',bsns_year,'&reprt_code=',reprt_code,
                   '&fs_div=OFS')
      fs_data_all = fromJSON(url)
      fs_data_all = fs_data_all[['list']]
    }
    
    #데이터 선택 후 열 이름을 연도로 변경
    yr_count = str_detect(colnames(fs_data_all),'trm_amount') %>% sum()
    yr_name = seq(bsns_year,(bsns_year - yr_count + 1))
    fs_data_all = fs_data_all[,c('corp_code','sj_nm','account_nm','account_detail')]%>%
      cbind(fs_data_all[,str_which(colnames(fs_data_all),'trm_amount')])
    colnames(fs_data_all)[str_which(colnames(fs_data_all),'amount')] = yr_name
  },error = function(e){
    #오류 발생 시 해당 종목명을 출력하고 다음 루프로 이동
    data_Fs <<- NA
    warning(paste0("Error in Ticker:",name))
  })
  #다운로드 받은 파일을 생성한 각각의 폴더 내 csv 파일로 저장
  #재무제표 저장
  write.csv(fs_data_all,paste0('data/dart_fs/',ticker_list$종목코드[i],'_fs_dart.csv'),
            fileEncoding = 'EUC-KR')
  Sys.sleep(2)
}
