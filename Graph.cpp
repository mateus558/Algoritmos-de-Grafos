#include "Graph.h"
#include <stack>
#include <iostream>

using namespace std;

Edge::Edge(int v){
	this->id = v;
	next = NULL;
}

Vertex::Vertex(){
	this->next = NULL;
	this->degree = 0;
	this->adjL = NULL;
}

Vertex::Vertex(int id){
	this->id = id;
}

//Por padrão o construtor cria um grafo vazio e nao-orientado
Graph::Graph(){
	this->nV = 0;
	this->nE = 0;
	isOriented = false;
	adjList = new Vertex;
}

Graph::Graph(int V, bool isOriented){
	this->isOriented = isOriented;
	this->nV = V;
	this->nE = 0;
	adjList = new Vertex;
	Vertex *itr = adjList;

	for(int i = 1; i <= V; i++){
		itr->id = i;
		if(i != V)
			itr->next = new Vertex;
		itr = itr->next;
	}
	
	itr = adjList;	
}

int Graph::getOrder(){
	return nV;
}

int Graph::getDegree(int v){
	Vertex *itr = adjList;
	
	while(itr != NULL && itr->id != v){
		itr = itr->next;
	}
	
	return (itr == NULL)?-1:itr->degree;
}

void Graph::addEdge(int u, int v){
	Vertex *itr = adjList;

	while(itr->id != u){
		itr = itr->next;
	}

	itr->degree++;

	Edge *eItr = itr->adjL;
	
	if(itr->adjL != NULL){
		while(eItr->next != NULL){
			eItr = eItr->next;
		}
		
		eItr->next = new Edge(v);
	}else{
		itr->adjL = new Edge(v);
	}
	
	nE++;	
		
	if(!isOriented){
		itr = adjList;
	
		while(itr->id != v){
			itr = itr->next;
		}
		
		itr->degree++;
		
		Edge *eItr = itr->adjL;

		if(itr->adjL != NULL){
			while(eItr->next != NULL){
				eItr = eItr->next;
			}			
			eItr->next = new Edge(u);	
		}else{
			itr->adjL = new Edge(u);
		}
		nE++;
	}
}

void Graph::addVertex(int v){
	Vertex *itr = adjList;
	
	while(itr->next != NULL){
		if(itr->next->id > v){
			break;
		}
		itr = itr->next;
	}

	if(itr->next == NULL){
		itr->next = new Vertex(v);
		nV++;
	}else if(itr->id > v){
		Vertex *temp = itr->next;
		itr->next = new Vertex(v);
		itr->next->next = temp;
		nV++;
	}else{
		cout << "Vertex " << v << " already exist" << endl;
	}
}

void Graph::deleteEdge(int u, int v){
	Vertex *itr = adjList;
		
	while(itr->next->id != u){
		itr = itr->next;
	}
		
	Edge *itrE = itr->adjL;
		
	while(itrE->next->id != v){
		itrE = itrE->next;
	}
			
	Edge *temp = itrE->next->next;
			
	delete itrE->next;
			
	itrE->next = temp;
}

void Graph::removeVertex(int v){
	Vertex *itr = adjList;
	
	while(itr != NULL && itr->next->id != v){
		itr = itr->next;
	}
	
	Edge *itrE = itr->adjL;
	stack<Edge*> stck;	
	
	if(!isOriented){
		while(itrE != NULL){
			stck.push(itrE);
			itrE = itrE->next;
		}
	}
	
	Vertex *temp = itr->next->next;
	
	delete itr->next;
	
	itr->next = temp;
	
	if(!isOriented){
		while(!stck.empty()){
			Edge *temp1 = stck.top();
			int id = temp1->id;
			this->deleteEdge(id, v);
			stck.pop();
		}
	}
}

int Graph::isRegular(){
	Vertex *itr = adjList;
	int degree = adjList->degree;
	
	while(itr != NULL && itr->degree == degree){
		itr = itr->next;
	}
	
	return (itr == NULL)?degree:-1;
}

bool Graph::isComplete(){
	Vertex *itr = adjList;
	
	while(itr != NULL && itr->degree == nV - 1){
		itr = itr->next;
	}
	
	return (itr == NULL);
}

void Graph::print(){
	Vertex *itr = adjList;
	
	while(itr != NULL){
		cout << itr->id << " ";
		Edge *itr1 = itr->adjL;
		
		while(itr1 != NULL){
			cout << itr1->id << " ";
			itr1 = itr1->next;
		}
		
		cout << endl;
		itr = itr->next;
	}
}

Vertex::~Vertex(){
	Vertex *current = next;
	degree = -1;
	id = -1;
	
	while(current != NULL){
		Vertex *prox = current->next;
		delete current->adjL;
		delete current;
		current = prox;
	}	

	next = NULL;
}

Edge::~Edge(){
	Edge *current = next;
	
	while(current != NULL){
		Edge *prox = current->next;
		delete current;
		current = prox;
	}	

	next = NULL; 
}

Graph::~Graph(){
	nV = 0;
	nE = 0;
	delete adjList;
	
	cout << "\nGraph deleted successfully!" << endl;
}
