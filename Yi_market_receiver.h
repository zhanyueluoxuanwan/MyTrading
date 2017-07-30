//used to receive market
#ifndef YI_MD_API
#define YI_MD_API
#include<iostream>
#include<string>
#include"TradeApi/CThostFtdcMdApi.h"
using namespace std;

namespace Yi{
class MyMarketApi: public CThostFtdcMdSpi{
public:
	//use mdapi to construct an instance
	MyMarketApi(CThostFtdcMdApi *mdapi);
	//construct connection
	void OnFrontConnected();
	//Response the login request
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	//Response the logout request
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//require market data
	void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//cancel market data
	void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//disconnected
	void OnFrontDisconnected(int nReason){};	

	//Response the logout request
	void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	

private:
	CThostFtdcMdApi *mymdapi;
	CThostFtdcReqUserLoginField *mylogin;
	int myloginID;
	string broker;
	string user_id;
	string password;
	string instrumentID;
}


}
