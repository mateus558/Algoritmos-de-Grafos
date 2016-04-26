all:
	g++ -g main.cpp Graph.h Graph.cpp -o main
	./main < grafo_125.txt
