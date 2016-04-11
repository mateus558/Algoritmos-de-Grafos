#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(){
	this->nV = 0;
	adj = NULL;
}

Graph::Graph(int V){
	this->nV = V;
	adj = new adjList(0);
	adjList *itr = adj;
	
	for(int i = 1; i < V; i++){
		itr->next = new adjList(i);
		itr->adjL = NULL;
		itr = itr->next;
	}
	
	itr = adj;
	/*while(itr != NULL){
		cout << itr->id << endl;
		itr = itr->next;
	}*/	
}

void Graph::addEdge(int u, int v){
	adjList *itr = adj;
	
	while(itr->id != u-1){
		itr = itr->next;
	}
	
	while(itr->adjL != NULL){
		itr = itr->adjL;
	}
	
	itr->adjL = new adjList(v-1);
	
	itr = adj;
	
	while(itr->id != v-1){
		itr = itr->next;
	}
	
	while(itr->adjL != NULL){
		itr = itr->adjL;
	}
	
	itr->adjL = new adjList(u-1);
}

void Graph::addVertex(int v){
	adjList *itr = adj;
	
	while(itr != NULL || itr->id < v-1){
		itr = itr->next;
	}
	
	if(itr == NULL){
		itr = new adjList(v - 1);
	}else if(itr->id >= v - 1){
		adjList *temp = itr->next;
		itr->next = new adjList(v - 1);
		itr->next->next = temp;
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

