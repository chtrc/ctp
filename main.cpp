#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "CTPMarketDataSource.h"
using namespace std;

std::string MdFront = "tcp://180.169.112.54:42213";

int main() {
    CThostFtdcMdApi *api = CThostFtdcMdApi::CreateFtdcMdApi();
    CTPMarketDataSource *mdSource = new CTPMarketDataSource(api);
    api->RegisterSpi(mdSource);
    api->RegisterFront(const_cast<char*>(MdFront.c_str()));
    cout<<"version: " << api->GetApiVersion() << endl;
    api->Init();
    api->Join();
    getchar();
    return 0;
}