all:
	g++ -g --std=c++11 main.cpp Graph.h Graph.cpp AdjacencyList.cpp -o main
	./main < grafo_125.txt
