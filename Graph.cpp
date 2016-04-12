#include "Graph.h"
#include <iostream>

using namespace std;

Edge::Edge(int v){
	this->id = v;
	next = NULL;
}

Vertex::Vertex(){
	this->adj = NULL;
}

Vertex::Vertex(int id){
	this->id = id;
	this->adj = NULL;
}

Graph::Graph(){
	this->nV = 0;
	isOriented = false;
}

Graph::Graph(int V, bool isOriented){
	this->isOriented = isOriented;
	this->nV = V;
	adjList = vector<Vertex*>(V+1);

	for(int i = 1; i <= V; i++){
		adjList[i] = new Vertex(i);
	}	
}

void Graph::addEdge(int u, int v){
	Edge *itr = adjList[u]->adj;
	
	if(itr != NULL){
		while(itr->next != NULL){
			itr = itr->next;
		}
		
		itr->next = new Edge(v);
	}else{
		adjList[u]->adj = new Edge(v);
	}
	
	if(!isOriented){
		itr = adjList[v]->adj;
		
		if(itr != NULL){
			while(itr->next != NULL){
				itr = itr->next;
			}		
			itr->next = new Edge(u);	
		}else{
			adjList[v]->adj = new Edge(u);
		}
	}
}

void Graph::addVertex(int v){
	
	if(adjList.size() > v){
		cout << "Vertex " << v << " already exist" << endl;
		return ;
	}
	
	vector<Vertex*> temp = adjList;
	vector<Vertex*> newAdj(nV + 2); 
	
	nV++;
	
	for(int i = 1; i < nV; i++){
		newAdj[i] = temp[i];
	} 
	
	newAdj[v] = new Vertex(v);
	adjList = newAdj;
}

void Graph::print(){
	for(int i = 1; i <= nV; i++){
		Edge *itr = adjList[i]->adj;
		cout << adjList[i]->id << " ";
		while(itr != NULL){
			cout << itr->id << " ";
			itr = itr->next;
		}
		cout << endl;
	}
}

