#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(){
	this->nV = 0;
	adj = NULL;
}

Graph::Graph(int V){
	this->nV = V;
	adj = new adjList(1);
	adjList *itr = adj;
	
	for(int i = 2; i <= V; i++){
		itr->next= new adjList(i);
		itr->adjL = NULL;
		itr = itr->next;
	}

	itr = adj;	
}

void Graph::addEdge(int u, int v){
	adjList *itr = adj;
	
	while(itr->id != u){
		itr = itr->next;
	}
	
	while(itr->adjL != NULL){
		itr = itr->adjL;
	}
	
	itr->adjL = new adjList(v);
	
	itr = adj;
	
	while(itr->id != v){
		itr = itr->next;
	}
	
	while(itr->adjL != NULL){
		itr = itr->adjL;
	}
	
	itr->adjL = new adjList(u);
}

void Graph::addVertex(int v){
	adjList *itr = adj;
	
	while(itr->next != NULL){
		if(itr->next->id > v){
			break;
		}
		itr = itr->next;
	}

	if(itr->next == NULL){
		itr->next = new adjList(v);
	}else if(itr->id > v){
		adjList *temp = itr->next;
		itr->next = new adjList(v);
		itr->next->next = temp;
	}else{
		cout << "Vertex " << v << " already exist" << endl;
	}
}

void Graph::print(){
	adjList *itr = adj;
	
	while(itr != NULL){
		cout << itr->id << " ";
		adjList *itr1 = itr->adjL;
		while(itr1 != NULL){
			cout << itr1->id << " ";
			itr1 = itr1->adjL;
		}
		cout << endl;
		itr = itr->next;
	}
}

