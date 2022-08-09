#include "CTPMarketDataSource.h"

std::string BrokerID = "0";
std::string InvestorID = "3620";
std::string Password = "123456";

char *ppInstrumentID[] = {(char*)"bu2302", (char*)"ag2304"};			// 行情订阅列表
int iInstrumentID = 2;	

CTPMarketDataSource::~CTPMarketDataSource(){}

CTPMarketDataSource::CTPMarketDataSource(CThostFtdcMdApi *api) {
    this->m_pMdUserApi = api;
}

void CTPMarketDataSource::OnFrontConnected()
{
    printf("front connected!\n");
    CThostFtdcReqUserLoginField loginReq;
    // std::string BrokerID, InvestorID, Password;
    memset(&loginReq, 0, sizeof(loginReq));
    strcpy(loginReq.BrokerID, BrokerID.c_str());
    strcpy(loginReq.UserID, InvestorID.c_str());
    strcpy(loginReq.Password, Password.c_str());
    static int requestID = 0;
    int rt = m_pMdUserApi->ReqUserLogin(&loginReq, requestID++);
}
 
void CTPMarketDataSource::OnFrontDisconnected(int nReason)
{
    printf("front disconnected!\n");
}
 
void CTPMarketDataSource::OnHeartBeatWarning(int nTimeLapse)
{
    printf("beat\n");
}

void CTPMarketDataSource::OnRspUserLogin(
            CThostFtdcRspUserLoginField *pRspUserLogin,
            CThostFtdcRspInfoField *pRspInfo,
            int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (bIsLast && !bResult)
    {   
        printf("账户登录成功\n");
        printf("交易日： %s\n", pRspUserLogin->TradingDay);
        printf("登录时间： %s\n", pRspUserLogin->LoginTime);
        printf("经纪商： %s\n", pRspUserLogin->BrokerID);
        printf("账户名： %s\n", pRspUserLogin->UserID);
        printf("SystemName： %s\n", pRspUserLogin->SystemName);
        printf("ApiVersion: %s\n", m_pMdUserApi->GetApiVersion());
 
        // 开始订阅行情
        int rt = m_pMdUserApi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
    } else {
        printf("login failed!\n");
    }
}
 
void CTPMarketDataSource::OnRspUserLogout(
                    CThostFtdcUserLogoutField *pUserLogout,
                    CThostFtdcRspInfoField *pRspInfo,
                    int nRequestID, bool bIsLast)
{
    printf("logout\n");
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
}
 
void CTPMarketDataSource::OnRspError(CThostFtdcRspInfoField *pRspInfo, 
        int nRequestID, bool bIsLast)
{
    printf("rsp error\n");
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
}
 
void CTPMarketDataSource::OnRspSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo,
            int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        // 订阅成功
        printf("subscribe successful. instrumentID: %s\n", pSpecificInstrument->InstrumentID);
    } else {
        printf("subscribe failed. ErrID: %d, ErrInfo: %s\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
    }
}
 
void CTPMarketDataSource::OnRspUnSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo,
            int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    printf("instrusment id: %s, len: %d\n", pSpecificInstrument->InstrumentID, (int)strlen(pSpecificInstrument->InstrumentID));
    // printf("%s\n", pRspInfo->ErrorMsg);
    std::cout<<pRspInfo->ErrorMsg<<" "<<pRspInfo->ErrorID<<std::endl;
    FILE *f = fopen("out.txt","a+");
    if(f != nullptr) {
        fwrite(pRspInfo->ErrorMsg,1,strlen(pRspInfo->ErrorMsg),f);
        fclose(f);
    }
    
}
 
 
int count = 0;
void CTPMarketDataSource::OnRtnDepthMarketData(
                CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    printf("\n -------------------------- \n");
    printf("count: %d\n", count++);
    printf("TradingDay: %s\n", pDepthMarketData->ActionDay);
    printf("InstrumentID: %s\n", pDepthMarketData->InstrumentID);
    printf("ExchangeID: %s\n", pDepthMarketData->ExchangeID);
    printf("ExchangeInstID: %s\n", pDepthMarketData->ExchangeInstID);
    printf("LastPrice: %lf\n", pDepthMarketData->LastPrice);
    printf("PreSettlementPrice: %lf\n", pDepthMarketData->PreSettlementPrice);
    printf("PreClosePrice: %lf\n", pDepthMarketData->PreClosePrice);
}