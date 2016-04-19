all:
	g++ -g main.cpp Graph.h Graph.cpp -o main
	./main < input.txt
