CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system
CFLAGS+= -pthread
LDFLAGS+= -pthread

all: Boost_Echo_Client12

Boost_Echo_Client12: bin/MainClient.o bin/FromServerReader.o bin/KeyboardReader.o bin/ConnectionHandler.o bin/Inventory.o bin/User.o    bin/MessageType.o
		g++ -o bin/Client bin/FromServerReader.o bin/KeyboardReader.o bin/MainClient.o bin/ConnectionHandler.o bin/Inventory.o bin/User.o   bin/MessageType.o $(LDFLAGS)


bin/MainClient.o: src/MainClient.cpp
	g++ $(CFLAGS) -o bin/MainClient.o src/MainClient.cpp


bin/FromServerReader.o: src/FromServerReader.cpp include/FromServerReader.h
	g++ $(CFLAGS) -o bin/FromServerReader.o src/FromServerReader.cpp


bin/KeyboardReader.o: src/KeyboardReader.cpp include/KeyboardReader.h
	g++ $(CFLAGS) -o bin/KeyboardReader.o src/KeyboardReader.cpp

bin/ConnectionHandler.o: src/ConnectionHandler.cpp include/ConnectionHandler.h
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/Inventory.o: src/Inventory.cpp include/Inventory.h
	g++ $(CFLAGS) -o bin/Inventory.o src/Inventory.cpp

bin/User.o: src/User.cpp include/User.h
	g++ $(CFLAGS) -o bin/User.o src/User.cpp

bin/MessageType.o: src/MessageType.cpp include/MessageType.h
	g++ $(CFLAGS) -o bin/MessageType.o src/MessageType.cpp

.PHONY: clean
clean:
	rm -f bin/*
