#ifndef GRAPH_H_
#define GRAPH_H_
#include <iostream>

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

struct AdjacencyList{
	Vertex *head;
	Vertex *middle;
	Vertex *tail;
	
	AdjacencyList(){
		head = NULL;
		middle = NULL;
		tail = NULL;
	}
	
	void insert(int i){
		Vertex *new_vertex = new Vertex(i);
		
		if(head == NULL){
			new_vertex->prev = tail;
			head = new_vertex;
			tail = new_vertex;
		}else{
			new_vertex->prev = tail;
			tail->next = new_vertex;
			tail = new_vertex;
		}
	}
	
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
	//Vertex* getDest(int v);
	Edge* getAdjacents(int v);
	int getMaxGraphDegree();
	void geraCompleto();
	int getVertexDegree(int v);
	int isRegular();
	bool isComplete();
	~Graph();
};

#endif
