#include<iostream>
#include<cstring>
#include"Yi_market_receiver.h"
#include"Yi_parameters.h"
#include "./TradeApi/ThostFtdcUserApiStruct.h"
using namespace std;

namespace Yi{
	MyMarketApi::MyMarketApi(CThostFtdcMdApi *mdapi){
		this->mymdapi = mdapi;
		this->myloginID = 10;				
	}
	
	void MyMarketApi::OnFrontConnected(){
	//processing connected operation
		broker = BROKER_ID;
		user_id = USER_ID;
		password = USER_PWD; 
		std::cout<< "Connected" << endl;
		mylogin = new CThostFtdcReqUserLoginField();
		strcpy(mylogin->BrokerID, broker.c_str());
		strcpy(mylogin->UserID, user_id.c_str());
		strcpy(mylogin->Password, password.c_str());
	    mymdapi->ReqUserLogin(mylogin, myloginID);	
	}
	
	void MyMarketApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout << "Request login\n";
		cout << "Trading day:" << mymdapi->GetTradingDay() << endl;		
		if (pRspInfo->ErrorID == 0){
			cout << "Success login-->ID: " << myloginID << endl;
			cout << "Requiring market data!" << endl;
			string tmp = INSTRUMENT;
			*instrumentID = const_cast<char*>(tmp.c_str());
			mymdapi->SubscribeMarketData(instrumentID, 1);
		}
	}

	void MyMarketApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	void MyMarketApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout << "Market data respones" << endl;
	        cout << "Instruments:" << pSpecificInstrument->InstrumentID << endl;
		cout << "ResponseInfo:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
	}

	void MyMarketApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	};

}
