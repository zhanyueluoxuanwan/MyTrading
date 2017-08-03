#include"Yi_market_receiver.h"
#include"Yi_parameters.h"
#include "./TradeApi/ThostFtdcUserApiStruct.h"
using namespace std;

namespace Yi{
	MyMarketApi::MyMarketApi(CThostFtdcMdApi *mdapi){
		//init api
		mymdapi = mdapi;
		myloginID = 10;
		//creating market file
		time_t now = time(0);		
		market_time = localtime(&now);
		market_file_name = MARKET_FILE + std::to_string(market_time->tm_year) + std::to_string(market_time->tm_mon) + std::to_string(market_time->tm_mday) + ".csv";
		market_file.open(market_file_name);
		cout << "Creating market file: " << market_file_name << endl;
		if(market_file.is_open())
			cout<< "Successful creating market file" << endl;			
		else	
			cout<< "Error in creating file" << endl;

		//reading instruments
		ifstream instrumentFile("InstrumentID.txt");
		if(instrumentFile.is_open()){
			string len;
		   	getline(instrumentFile,len);
			instrumentNum = stoi(len);
			*instrumentID = (char *)malloc(sizeof(char*) * instrumentNum);
			for(int line = 0; line < instrumentNum; line++){
				string instrument;
			   	getline(instrumentFile,instrument); 
				instrumentID[line] = (char *)malloc(sizeof(char) * instrument.length());
				strcpy(instrumentID[line], instrument.c_str());	
			}
		}
		else
			cout<<"Cannot read instruments!" << endl;

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
			int ret = mymdapi->SubscribeMarketData(instrumentID, instrumentNum);
			cout << ((ret == 0)?"Successful subscribe!" : "Failed subscribe!") << endl;
		}
	}

	void MyMarketApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	void MyMarketApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
		cout << "Market data respones" << endl;
	        cout << "Instruments:" << pSpecificInstrument->InstrumentID << endl;
		cout << "ResponseInfo:" << pRspInfo->ErrorID << " " << pRspInfo->ErrorMsg << endl;
	}

	void MyMarketApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *MarketData){
	
	};

	void MyMarketApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){
	};

}
