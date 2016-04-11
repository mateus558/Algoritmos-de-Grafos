#ifndef GRAPH_H_
#define GRAPH_H_

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
	Graph();
	Graph(int V);
	void print();
	void addVertex(int v);
	void addEdge(int u, int v);
	void deleteEdge(int u, int v);
	
};

#endif
