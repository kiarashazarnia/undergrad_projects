royale: game.o main_royale.o
	g++ game.o main_royale.o -o royale
game.o: game.cpp game.hpp
	g++ game.cpp -c
main_royale.o: main_royale.cpp game.hpp
	g++ main_royale.cpp -c
debug:
	g++ *.cpp -o royale -g
	gdb royale -tui
clean:
	rm *.o royale