#ifndef GRAPH_H_
#define GRAPH_H_
#include <assert.h>
#include <iostream>

using namespace std;

class Vertex{
	int id;
};

class Edge{
	int weight;
};

struct adjList{
	int id;
	adjList *next;
	adjList *adjL;
	
	adjList(int id){
		this->id = id;
	}	
};

class Graph{
private:
	int nV;
	adjList *adj;
public:
	Graph(int V);
	void addEdge(int u, int v);
	void deleteEdge(int u, int v);
	
};

#endif
