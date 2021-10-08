CPP11 = g++ -std=c++11
LFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
OBJ = pages.o main.o game.o draws.o rsdl.o

PandaKungFu.out: $(OBJ)
	$(CPP11) $(OBJ) $(LFLAGS) -o PandaKungFu.out

pages.o:	pages.cpp pages.hpp defines.hpp
	$(CPP11) pages.cpp -c

main.o:		main.cpp game.hpp defines.hpp
	$(CPP11) main.cpp -c

game.o:		game.cpp game.hpp defines.hpp
	$(CPP11) game.cpp -c

draws.o:	draws.cpp game.hpp defines.hpp
	$(CPP11) draws.cpp -c

rsdl.o:	rsdl.cpp rsdl.hpp
	$(CPP11) rsdl.cpp -c

clean:
	rm *.o *.out

debug:
	$(CPP11) *.cpp $(LFLAGS) -g -o debugging.out

war:
	$(CPP11) *.cpp -c -Wall
	$(CPP11) *.o $(LFLAGS) -Wall -o temp.out

test:	PandaKungFu.out
	./PandaKungFu.out
