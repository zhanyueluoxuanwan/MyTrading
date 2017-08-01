#C++ compiler
CC = g++

#enable warning, 64bit compiler
CXXFLAGS = -Wall -fPIC

#obj files
OBJ = Yi_market_receiver.o main.o

#final program
TARGET = trade_platform

#compiling rules
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

#fine compiling rules
Yi_market_receiver.o : Yi_market_receiver.h
main.o : Yi_market_receiver.o

#pseudo command
.PHONY : clean
clean : 
	rm trade_platform $(OBJ)
