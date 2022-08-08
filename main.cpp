#include <iostream>
#include "ThostFtdcTraderApi.h"
#include "ThostFtdcMdApi.h"
#include "CTPMarketDataSource.h"
using namespace std;

std::string MdFront = "tcp://122.51.136.165:20004";

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