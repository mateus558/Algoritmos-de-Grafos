#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <ctime>
#include <utility> 
#include <stack>

using namespace std;

class Edge;

struct Vertex{
	int id;
	int degree;
	Vertex *prev;
	Vertex *next;
	Edge *adjL;

	Vertex();
	Vertex(int id);
	~Vertex();
};

struct Edge{
	int id;
	int weight;
	Vertex *dest;
	Edge *next;

	Edge(Vertex *v, int weight);
	Edge(Vertex *v);
	~Edge();
};

typedef pair<Vertex*, Vertex*> PairV;

class AdjacencyList{
private:
	Vertex *head;
	Vertex *middle;
	Vertex *tail;
public:	
	AdjacencyList();
	void push_front(int i);
	void deleteEdge(int u, int v);
	PairV addEdge(PairV destins, int u, int v, int weight, int it);
	friend class Graph;
};

class Graph{
private:
	int nV;	//Cardinalidade do conjunto V de vertices
	int nE;	//Cardinalidade do conjunto E de arestas ou arcos
	int degree;	//Grau maximo do grafo
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	AdjacencyList *adjList;	//Lista de adjacências
	void auxDeleteEdge(int u, int v);
public:
	Graph();	
	Graph(int V, bool isOriented);
	void print();
	void addVertex(int v);
	void removeVertex(int v);
	void addEdge(int u, int v, int weight);
	void deleteEdge(int u, int v);
	int getOrder();
	int size();
	Edge* getAdjacents(int v);
	int getMaxGraphDegree();
	void geraCompleto();
	int getVertexDegree(int v);
	int isRegular();
	bool isComplete();
	~Graph();
};

#endif
