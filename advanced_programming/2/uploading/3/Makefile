all:
	g++ main.cpp functions.cpp

1: main.o
	g++ main.o functions.o

2: functions.o
	g++ main.o functions.o

3: main.cpp
	g++ main.cpp -c -o main.o

4: functions.cpp
	g++ functions.cpp -c -o functions.o

5: header.h
	g++ main.cpp functions.cpp

debug:
	g++ main.cpp functions.cpp -g
