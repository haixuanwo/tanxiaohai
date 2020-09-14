
CXX=g++
RM=rm
SRC=main.cpp \
	src/log.cpp \
	src/mqtt.cpp \
	src/tinyxml2.cpp \
	src/sqlite.cpp \
	src/Time.cpp \
	src/random_number.cpp

CFLAGS=-llog4cpp -lmosquitto -lsqlite3 -lm -ldl -lpthread -std=c++11
BIN=main
INC=include
LIB=lib

all:
	$(CXX) -I$(INC) -L$(LIB) $(SRC) $(CFLAGS) -o $(BIN)

clean:
	$(RM) -rf $(BIN) *.o

.PHONY : clean

