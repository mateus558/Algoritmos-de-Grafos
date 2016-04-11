#ifndef GRAPH_H_
#define GRAPH_H_

class adjList{
	int id;
	adjList *next;
	adjList *adjL;

	public:
	adjList();
	adjList(int id){
		this->id = id;
	}
	
	friend class Graph;	
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
