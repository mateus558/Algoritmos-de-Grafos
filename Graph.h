#ifndef GRAPH_H_
#define GRAPH_H_
#define INF 1000000000
#define NIL -1
#define min(a,b) ((a < b)?(a:b))
#include <iostream>
#include <ctime>
#include <utility> 
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <sstream>
#include <climits>
#include "UnionFind.h"

using namespace std;

struct Edge;

struct Vertex{
	int id;
	int d;
	Vertex *dad;
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
	Vertex *ini;
	Vertex *dest;
	Edge *next;
	
	Edge(int v, int weight);
	Edge(Vertex *v, int weight);
	Edge(Vertex *u, Vertex *v, int weight);
	Edge(Vertex *v);
	~Edge();
};

typedef vector<vector<int> > Matrix;
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
	vector<int> dist;
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	AdjacencyList *adjList;	//Lista de adjacências
	void auxDeleteEdge(int, int);
	void countComponents(Vertex*, int&, int*);
	void DFSUtil(int, bool*);
	void isBipartiteUtil(Vertex*, bool*, int&, int*, bool&);
	vector<Vertex*> initializeSingleSource(vector<Vertex*>, int);
	vector<Vertex*> relax(Edge*, Vertex*, vector<Vertex*>, int*, int);
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
	int djkstra(int, int);
	int MSTKruskal();
	int MSTPrim();
	list<Vertex*> directTransitiveClosure(int v);
	list<Vertex*> indirectTransitiveClosure(int v);
	AdjacencyList* transposeGraph();
	Matrix getWeightMatrix();
	Matrix floydWarshall(Matrix);
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
