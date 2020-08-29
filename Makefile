
CXX=g++
RM=rm
SRC=main.cpp src/log.cpp
CFLAGS=-llog4cpp -lpthread -std=c++11
BIN=main

all:
	$(CXX) -Iinclude -Llib $(SRC) $(CFLAGS) -o $(BIN)

clean:
	$(RM) -rf $(BIN) *.o

.PHONY : clean

