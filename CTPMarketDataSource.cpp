#include "CTPMarketDataSource.h"

std::string BrokerID = "0";
std::string InvestorID = "3620";
std::string Password = "123456";

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

char *ppInstrumentID[] = {"cu1710", "cu1801"};			// 行情订阅列表
int iInstrumentID = 2;	

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
    printf("rsp sub marketdata\n");
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    if (!bResult)
    {
        // 订阅成功
    }
}
 
void CTPMarketDataSource::OnRspUnSubMarketData(
            CThostFtdcSpecificInstrumentField *pSpecificInstrument,
            CThostFtdcRspInfoField *pRspInfo,
            int nRequestID, bool bIsLast)
{
    bool bResult = pRspInfo && (pRspInfo->ErrorID != 0);
    printf("instrusment id: %s, len: %d\n", pSpecificInstrument->InstrumentID, strlen(pSpecificInstrument->InstrumentID));
    // printf("%s\n", pRspInfo->ErrorMsg);
    std::cout<<pRspInfo->ErrorMsg<<" "<<pRspInfo->ErrorID<<std::endl;
    FILE *f = fopen("out.txt","w+");
    fwrite(pRspInfo->ErrorMsg,1,20,f);
}
 
 
 
void CTPMarketDataSource::OnRtnDepthMarketData(
                CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    printf("OnRtnDepthMarketData\n");
    // 接收行情数据
    // 处理订阅合约行情数据
}