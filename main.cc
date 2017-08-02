#include<iostream>
#include"./TradeApi/ThostFtdcMdApi.h"
#include"./TradeApi/ThostFtdcTraderApi.h"
#include"Yi_market_receiver.h"
#include"Yi_parameters.h"
using namespace std;
using namespace Yi;

int main(int argc, char **argv){
	//testing the connection
	CThostFtdcMdApi *mdapi = 
		CThostFtdcMdApi::CreateFtdcMdApi("/home/james/quant/data", true);
	MyMarketApi mymdapi(mdapi);
	mdapi->RegisterSpi(&mymdapi);
	mdapi->RegisterFront(MARKET_FRONT_IP);
	std::cout<<"Registration Success!"<<endl;
	mdapi->Init();
	std::cout<<"Init API Success!"<<endl;
	mdapi->Join();
	std::cout<<"Start Thread Success!"<<endl;
	mdapi->Release();
	std::cout<<"Stop Thread Success!"<<endl;
	std::cout<<"The Start of Glory!"<<endl;
	return 0;
}
