CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=bin
FLAGS = -std=c++11 -g
OBJ = $(BUILD_DIR)/message.o $(BUILD_DIR)/user.o $(BUILD_DIR)/main.o $(BUILD_DIR)/implementation.o $(BUILD_DIR)/common.o $(BUILD_DIR)/web_interface.o $(BUILD_DIR)/content.o $(BUILD_DIR)/webhandler.o
PRE = $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o

all: $(BUILD_DIR) jeeker.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: src/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

jeeker.out: $(OBJ) $(PRE)
	$(CC) $(CF) $(OBJ) $(PRE) -o jeeker.out

$(BUILD_DIR)/common.o:	src/common.cpp src/common.hpp
	g++ src/common.cpp -c -o $(BUILD_DIR)/common.o $(FLAGS)

$(BUILD_DIR)/message.o:	src/message.cpp src/message.hpp	src/common.hpp src/user.hpp
	g++ src/message.cpp -c -o $(BUILD_DIR)/message.o $(FLAGS)

$(BUILD_DIR)/content.o:	src/content.cpp src/content.hpp	src/common.hpp
	g++ src/content.cpp -c -o $(BUILD_DIR)/content.o $(FLAGS)

$(BUILD_DIR)/webhandler.o:	src/webhandler.cpp src/webhandler.hpp	src/common.hpp
	g++ src/webhandler.cpp -c -o $(BUILD_DIR)/webhandler.o $(FLAGS)

$(BUILD_DIR)/user.o: src/user.cpp src/user.hpp src/common.hpp src/message.hpp
	g++ src/user.cpp -c -o $(BUILD_DIR)/user.o $(FLAGS)

$(BUILD_DIR)/main.o: src/main.cpp src/common.hpp
	g++ src/main.cpp -c -o $(BUILD_DIR)/main.o $(FLAGS)

$(BUILD_DIR)/implementation.o: src/implementation.cpp	src/common.hpp	src/user.hpp
	g++ src/implementation.cpp -c -o $(BUILD_DIR)/implementation.o $(FLAGS)

$(BUILD_DIR)/web_interface.o: src/web_interface.cpp src/web_interface.hpp
	g++ src/web_interface.cpp -c -o $(BUILD_DIR)/web_interface.o $(FLAGS)
	
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
