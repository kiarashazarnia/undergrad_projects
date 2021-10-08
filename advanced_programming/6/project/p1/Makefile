a.out:	main_expression.o tree.o
	g++ main_expression.o tree.o
main_expression.o: main_expression.cpp tree.hpp
	g++ main_expression.cpp -c
tree.o: tree.cpp tree.hpp
	g++ tree.cpp -c
debug:
	g++ *.cpp -g -Wall
clean:
	rm *.o *.out