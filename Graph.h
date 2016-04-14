#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>

struct Edge;

class Vertex{
private:
	int id;
	int degree;
	Edge *adj;
public:
	Vertex();
	Vertex(int id);
	~Vertex();
	friend class Graph;	
};

struct Edge{
	int id;
	Edge *next;

	Edge(int v);
};

class Graph{
private:
	int nV;	//Número de Vértices
	int nE;	//Número de arestas
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	std::vector<Vertex*> adjList;	//Lista de adjacências
public:
	Graph();
	Graph(int V, bool isOriented);
	void print();
	void addVertex(int v);
	void addEdge(int u, int v);
	void deleteEdge(int u, int v);
	int getOrder();
	int getDegree(int v);
	~Graph();
	
};

#endif
