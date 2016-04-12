#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>

struct Edge;

class Vertex{
private:
	int id;
	Edge *adj;
public:
	Vertex();
	Vertex(int id);
	friend class Graph;	
};

struct Edge{
	int id;
	Edge *next;

	Edge(int v);
};

class Graph{
private:
	int nV;
	bool isOriented;
	std::vector<Vertex*> adjList;
public:
	Graph();
	Graph(int V, bool isOriented);
	void print();
	void addVertex(int v);
	void addEdge(int u, int v);
	void deleteEdge(int u, int v);
	
};

#endif
