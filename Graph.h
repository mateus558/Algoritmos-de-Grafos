#ifndef GRAPH_H_
#define GRAPH_H_

struct Edge;

class Vertex{
private:
	int id;
	Vertex *next;
	Edge *adjL;

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
	~Edge();
};

class Graph{
private:
	int nV;	//Número de Vértices
	int nE;	//Número de arestas
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	Vertex *adjList;	//Lista de adjacências
public:
	Graph();	
	Graph(int V, bool isOriented);
	void print();
	void addVertex(int v);
	void addEdge(int u, int v);
	void deleteEdge(int u, int v);
	~Graph();
};

#endif
