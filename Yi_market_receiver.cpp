#include"Yi_maket_receiver.h"
#include"Yi_parameters.h"
#include "TradeApi/ThostFtdcUserApiStruct.h"
using namespace std;

namespace Yi{
	MyMarketApi::MyMarketApi(CThostFtdcMdApi *mdapi){
		this->mymdapi = mdapi;
		this->mylogin = 10;				
	}
	
	void MyMarketApi::OnFrontConnected(){
	//processing connected operation
		broker = BROKER_ID;
		user_id = USER_ID;
		password = USER_PWD; 
		std::cout<< "Connected" << endl;
		mylogin = new CThostFtdcMdApi();
		strcpy(loginField->BrokerID, broker.c_str());
	        strcpy(loginField->UserID, user_id.c_str());
	        strcpy(loginField->Password, password.c_str());
	        mdapi->ReqUserLogin(loginField, loginRequestID);	
	}
	
	void MdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout << "Request login\n";
		cout << "Trading day:" << mdapi->GetTradingDay() << endl;		
		if (pRspInfo->ErrorID == 0){
			cout << "Success login-->ID: " << loginRequestID << endl;
			cout << "Requiring market data!" << endl;
			instrumentID = INSTRUMENT;
			mdapi->SubscribeMarketData(instrumentID, 1);
		}
	}
	void MdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout << "Market data respones" << endl;
	        cout << "Instruments:" << pSpecificInstrument->InstrumentID << endl;
		cout << "ResponseInfo:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
	}


}
