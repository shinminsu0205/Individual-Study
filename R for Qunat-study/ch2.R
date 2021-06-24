#aapl data crawling(via quandl)
url.aapl = "https://www.quandl.com/api/v3/datasets/WIKI/AAPL/data.csv?api_key=xw3NU3xLUZ7vZgrz5QnG"
data.aapl = read.csv(url.aapl)

head(data.aapl)

#getSymbols(via yahoofinance)
library(quantmod)
getSymbols('AAPL')

head(AAPL)
chart_Series(Ad(AAPL)) #adjusted charts

data = getSymbols('AAPL',from = '2000-01-01', to = '2018-12-31', auto.assign = FALSE)
#auto.assign = False : save the data with designated name not the ticker name automatically
head(data)

ticker = c('FB','NVDA')
getSymbols(ticker)

head(FB)
head(NVDA)

getSymbols('005930.KS',from = '2000-01-01', to = '2018-12-31')
tail(Ad(`005930.KS`)) #뒤에 .KS 때문에 `를 붙여줘야 ADJUSTED를 들고 올 수 있음
tail(Cl(`005930.KS`))

getSymbols('068760.KQ', from = '2000-01-01', to = '2018-12-31')
tail(Cl(`068760.KQ`))

#FRED 데이터 다운로드
getSymbols('DGS10',src='FRED')
chart_Series(DGS10)
getSymbols('DEXKOUS',src='FRED')
chart_Series(DEXKOUS)
