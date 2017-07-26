#include"Yi_maket_receiver.h"
#include"Yi_parameters.h"
#include "TradeApi/ThostFtdcUserApiStruct.h"
using namespace std;

namespace Yi{
	MyMarketAPi::MyMarketAPi(CThostFtdcMdApi *mdapi){
		this->mymdapi = mdapi;
		this->mylogin = 10;				
	}
}
