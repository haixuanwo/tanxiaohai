
CXX=g++
RM=rm
SRC=main.cpp src/log.cpp src/mqtt.cpp src/tinyxml2.cpp
CFLAGS=-llog4cpp -lmosquitto -lpthread -std=c++11 -g
BIN=mqtt_main
INC=include
LIB=lib

all:
	$(CXX) -I$(INC) -L$(LIB) $(SRC) $(CFLAGS) -o $(BIN)

clean:
	$(RM) -rf $(BIN) *.o

.PHONY : clean

