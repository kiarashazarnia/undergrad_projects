FLAGS = -std=c++11 -g
OBJ = bin/message.o bin/command.o bin/user.o bin/main.o bin/implementation.o bin/common.o bin/text_interface.o

jeeker.out: $(OBJ)
	g++ $(OBJ) -o jeeker.out $(FLAGS) 

bin/common.o:	common.cpp	common.hpp
	g++ common.cpp -c -o bin/common.o $(FLAGS)
bin/message.o:	message.cpp message.hpp	common.hpp	user.hpp
	g++ message.cpp -c -o bin/message.o $(FLAGS)
bin/command.o:	command.cpp command.hpp	common.hpp
	g++ command.cpp -c -o bin/command.o $(FLAGS) 
bin/user.o:		user.cpp user.hpp		common.hpp	message.hpp
	g++ user.cpp -c -o bin/user.o $(FLAGS)
bin/main.o:		main.cpp	common.hpp
	g++ main.cpp -c -o bin/main.o $(FLAGS)
bin/implementation.o: implementation.cpp	common.hpp	user.hpp command.hpp
	g++ implementation.cpp -c -o bin/implementation.o $(FLAGS)
bin/text_interface.o: text_interface.cpp	text_interface.hpp
	g++ text_interface.cpp -c -o bin/text_interface.o $(FLAGS)
	
war:
	g++ *.cpp $(FLAGS) -Wall -o temp
	rm temp
debug: jeeker.out
	gdb jeeker.out -tui
remove:
	rm *.out *.o bin/*
