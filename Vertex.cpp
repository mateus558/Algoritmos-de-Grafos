#include "Graph.h"

Vertex::Vertex(){
	this->next = NULL;
	this->degree = 0;
	this->adjL = NULL;
}

/*
 ======================= Vertex(int id) =======================

 	Inicializa um vértice com um id.
	 	
 	Parametros:
 	
 	int id -> Inteiro representando o id do vertice. 
*/
Vertex::Vertex(int id){
	this->id = id;
	this->next = NULL;
	this->degree = 0;
	this->adjL = NULL;
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
