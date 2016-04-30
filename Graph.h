#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <ctime>
#include <utility> 
#include <stack>
#include <vector>
#include <cstdint>

using namespace std;

struct Edge;

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
	void push_back(int i);
	void deleteEdge(int u, int v);
	PairV addEdge(PairV destins, int u, int v, int weight, int it);
	friend class Graph;
};

class Graph{
private:
	int nV;	//Cardinalidade do conjunto V de vertices
	int nE;	//Cardinalidade do conjunto E de arestas ou arcos
	int degree;	//Grau maximo do grafo
	int maxId;
	static int removed;
	static int ins;
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	AdjacencyList *adjList;	//Lista de adjacências
	void auxDeleteEdge(int u, int v);
public:
	Graph();	
	Graph(int V, bool isOriented);
	void print();
	bool isAdjacent(int, int);
	void addVertex(int);
	void removeVertex(int);
	void addEdge(int, int, int);
	void deleteEdge(int, int);
	int getOrder();
	void DFS();
	void DFSUtil(int, bool*);
	bool isConnected();
	int size();
	vector<Edge*> getAdjacents(int);
	int getMaxGraphDegree();
	Vertex* getBegin(int);
	void geraCompleto();
	int getVertexDegree(int);
	int isRegular();
	bool isBipartite();
	void isBipartiteUtil(int, bool*, int&, int8_t*, bool&);
	bool isComplete();
	~Graph();
	friend class AdjacencyList;
};

#endif
