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

int Graph::getVertexDegree(int v){
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
	Edge *dad = eItr;
	if(itr->adjL != NULL){
		while(eItr != NULL && eItr->id <= v){
			dad = eItr;
			eItr = eItr->next;
		}

		Edge *new_edge = new Edge(v);
		new_edge->next = eItr;
		dad->next = new_edge;
	}else itr->adjL = new Edge(v);
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
	Vertex *dad = itr;
	
	while(itr != NULL && itr->id <= v){
		dad = itr;
		itr = itr->next;
	}
	
	Vertex *new_vertex = new Vertex(v);

	new_vertex->next = itr;
	dad->next = new_vertex;
}
//Por algum motivo está deletando o vértice errado, lembrar de acertar
void Graph::auxDeleteEdge(int u, int v){
	Vertex *itr = adjList;

	while(itr != NULL && itr->id != u){
		itr = itr->next;
	}

	Edge *adj = itr->adjL;	
	Edge *prev = adj;

	while(adj != NULL && adj->id != v){
		prev = adj;
		adj = adj->next;
	}	
	
	if(adj == itr->adjL){
		Edge *temp = adj->next;
		itr->adjL = NULL;
		itr->adjL = temp;
	}else{
		prev->next = adj->next;
	}
}

void Graph::deleteEdge(int u, int v){
	this->auxDeleteEdge(u, v);
	
	if(!isOriented){
		this->auxDeleteEdge(v, u);
	}	
}
//Terminar depois
void Graph::removeVertex(int v){
	Vertex *itr = adjList;
	Vertex *prev = itr;
	cout <<"removing "<< v <<endl;
	while(itr != NULL && itr->id != v){
		prev = itr;
		itr = itr->next;
	}

	Edge *itrE = itr->adjL;
	stack<Edge*> stck;	
	Vertex *var = itr;
	
	if(!isOriented){
		while(itrE != NULL){
			stck.push(itrE);
			itrE = itrE->next;
		}
	}else{
		itr = adjList;
		while(itr != NULL){
			Edge *adj = itr->adjL;
			while(adj != NULL && adj->id != v){
				adj = adj->next;
			}	
			if(adj != NULL){
				this->deleteEdge(itr->id, adj->id);
			}
			itr = itr->next;
		}
	
	}

	if(!isOriented){
		while(!stck.empty()){
			Edge *temp1 = stck.top();
			int id = temp1->id;	
			this->deleteEdge(id, v);	
			stck.pop();
		}
	}
	Vertex *temp = var->next;
	
	prev->next = temp;
	var = temp;
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
	cout << endl;
}

Vertex::~Vertex(){
	Vertex *current = next;
	
	while(current != 0){
		Vertex *prox = current->next;
		delete current->adjL;
		delete current;
		current = prox;
	}	
	next = 0;
}

Edge::~Edge(){
	Edge *current = next;
	
	while(current != NULL){
		Edge *prox = current->next;
		delete current;
		current = prox;
	}
	next = NULL;
	cout << "deleted" << endl;
}

Graph::~Graph(){
	nV = 0;
	nE = 0;
	delete adjList;
	adjList = NULL;
	cout << "\nGraph deleted successfully!" << endl;
}
