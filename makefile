all:
	g++ -g --std=c++11 main.cpp Graph.h Graph.cpp -o main
	./main < grafo_125.txt
