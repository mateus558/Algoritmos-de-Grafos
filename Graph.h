#ifndef GRAPH_H_
#define GRAPH_H_

class Edge;

class Vertex{
private:
	int id;
	int degree;
	Vertex *next;
	Edge *adjL;

public:
	Vertex();
	Vertex(int id);
	~Vertex();
	friend class Edge;
	friend class Graph;	
};

class Edge{
private:
	int id;
	int weight;
	Vertex *dest;
	Edge *next;
public:
	Edge(Vertex *v, int weight);
	Edge(Vertex *v);
	~Edge();
	friend class Graph;
	friend class Vertex;
};

class Graph{
private:
	int nV;	//Cardinalidade do conjunto V de vertices
	int nE;	//Cardinalidade do conjunto E de arestas ou arcos
	int degree;	//Grau maximo do grafo
	bool isOriented;	//Booleano dizendo se o grafo é orientado
	Vertex *adjList;	//Lista de adjacências
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
