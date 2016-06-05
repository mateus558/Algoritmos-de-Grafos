#include "Graph.h"

Edge::Edge(Vertex *v, int weight){
	this->dest = v;
	this->id = v->id;
	this->weight = weight;
	next = NULL;
}

Edge::Edge(Vertex *u, Vertex *v, int weight){
	this->ini = u;
	this->dest = v;
	this->id = v->id;
	this->weight = weight;
	next = NULL;
}

Edge::Edge(int v, int weight){
	this->id = v;
	this->weight = weight;
	next = NULL;
}

Edge::Edge(Vertex *v){
	this->dest = v;
	this->id = v->id;
	next = NULL;
}



Edge::~Edge(){
	/*Edge *current = next;
	
	while(current != NULL){
		Edge *prox = current->next;
		delete current;
		current = prox;
	}
	next = NULL;*/
}
