link: main.o functions.o
	g++ main.o functions.o

main.o: main.cpp
	g++ main.cpp -c -o main.o

functions.cpp:
	g++ functions.cpp -c -o functions.o

header.h: header.h
	g++ main.cpp -c -o main.o
	g++ functions.cpp -c functions.o

clean:
	rm *.o

all:
	g++ main.cpp functions.cpp

debug:
	g++ main.cpp functions.cpp -g
