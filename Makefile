#C++ compiler
CC = g++

#enable warning, 64bit compiler
CXXFLAGS = -Wall -fPIC

#source files
CCFILES = Yi_market_receiver.cc main.cc

#obj files
OBJ = Yi_market_receiver.o main.o

#include files
INC = -I/home/james/MyTrading/TradeApi/

#library files
LIB = $(wildcard ./TradeApi/*.so) 
MY_LINK = -L$(LIB)

#final program
TARGET = trade_platform

#compiling rules
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(INC) $(MY_LINK)

main.o : Yi_market_receiver.o
	$(CC) $(CXXFLAGS) -o $@ -c main.cc $(INC) $(MY_LINK)
	
Yi_market_receiver.o : Yi_market_receiver.h Yi_market_receiver.cc
	$(CC) $(CXXFLAGS) -o $@ -c Yi_market_receiver.cc $(INC) $(MY_LINK) 

#pseudo command
.PHONY : clean
clean : 
	rm *.o
	find . -maxdepth 1 -type f -perm /111 -exec rm {} \;
