#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>
#include <ctime>
#include <utility> 
#include <stack>
#include <vector>
#include <sstream>

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
	
	Edge(int v, int weight);
	Edge(Vertex *v, int weight);
	Edge(Vertex *v);
	~Edge();
};

typedef pair<Vertex*, Vertex*> PairV;

struct AdjacencyList{
	Vertex *head;
	Vertex *tail;

	AdjacencyList();
	void push_front(int i);
	void push_back(int i);
	void deleteEdge(int u, int v);
	PairV addEdge(PairV destins, int u, int v, int weight, int it);
};

class Graph{
private:
	int nV;	//Cardinalidade do conjunto V de vertices
	int nE;	//Cardinalidade do conjunto E de arestas ou arcos
	int degree;	//Grau maximo do grafo
	int maxId;
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	AdjacencyList *adjList;	//Lista de adjacências
	void auxDeleteEdge(int, int);
	void countComponents(Vertex*, int&, int*);
	void DFSUtil(int, bool*);
	void isBipartiteUtil(Vertex*, bool*, int&, int*, bool&);
public:
	Graph();	
	Graph(int V, bool isOriented);
	string print();
	static bool ehOriented(vector<pair<int,int> >);
	bool isAdjacent(int, int);
	void addVertex(int);
	void removeVertex(int);
	void addEdge(int, int, int);
	void addEdge(int, int);
	void deleteEdge(int, int);
	bool isArticulation(int);
	int getWeight(int, int);
	int nConnectedComponents();
	int getOrder();
	bool isBridge(int, int);
	void DFS();
	Graph* complementaryGraph();
	bool exist(int v);
	bool isConnected();
	static AdjacencyList* inducedGraph(vector<int>, Graph*);
	int size();
	vector<Edge*> getAdjacents(int);
	int getMaxGraphDegree();
	Vertex* getBegin(int);
	void geraCompleto();
	int getVertexDegree(int);
	int isRegular();
	bool isBipartite();
	bool isComplete();
	~Graph();
	friend class AdjacencyList;
};

#endif
