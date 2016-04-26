#include "Graph.h"
#include <stack>
#include <iostream>

using namespace std;

Edge::Edge(Vertex *v, int weight){
	this->dest = v;
	this->id = v->id;
	this->weight = weight;
	next = NULL;
}

Edge::Edge(Vertex *v){
	this->dest = v;
	this->id = v->id;
	next = NULL;
}


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
}

/*
======================= Graph() =======================
	Construtor padrao do grafo, inicializa um grafo vazio.
	
*/
Graph::Graph(){
	this->nV = 0;
	this->nE = 0;
	this->degree = -1;
	isOriented = false;
	adjList = new Vertex;
}

/*
======================= Graph(int V, bool isOriented) =======================
	Construtor sobrecarregado do grafo para quando se quiser inicializar o grafo 
com uma quantidade inicial de vertices e definir se o grafo e orientado ou nao.

	Parametros:
	
	int V -> Tamanho inicial do conjunto de vertices V;
	bool isOriented -> Booleano para definir se o grafo é orientado ou nao. 
*/
Graph::Graph(int V, bool isOriented){
	this->isOriented = isOriented;
	this->nV = V;
	this->nE = 0;
	this->degree = -1;
	adjList = new Vertex;
	Vertex *itr = adjList;

	for(int i = 0; i < V; i++){
		itr->id = i;
		if(i != V)
			itr->next = new Vertex(i);
		itr = itr->next;
	}
	
}

int Graph::size(){
	return nE;
}

/*
======================= getMaxGraphDegree() =======================
	Retorna o grau do grafo.

	O grau de um grafo G = (V,E), é o grau máximo do conjunto V de
vértices pertencentes a G.

*/
int Graph::getMaxGraphDegree(){
	Vertex *itr = adjList;
	int maior = itr->degree;
	
	if(itr == NULL) return -1;
	
	while(itr != NULL){
		if(itr->degree > maior)
			maior = itr->degree;
			
		itr = itr->next;
	}
	
	return maior;
}

/*
 ======================= getOrder() =======================

 	Retorna a ordem do grafo.
 	A ordem de um grafo  é o seu numero de vertices. 
*/
int Graph::getOrder(){
	return nV;
}

/*
 ======================= getVertexDegree(int v) =======================

 	Retorna o grau de um vertice v.
	O grau de um vertice v e o numero de vertices adjacentes a v.
	 	
 	Parametros:
 	
 	int v -> Inteiro representando o id do vertice. 
*/
int Graph::getVertexDegree(int v){
	Vertex *itr = adjList;
	
	while(itr != NULL && itr->id != v){
		itr = itr->next;
	}
	
	return (itr == NULL)?-1:itr->degree;
}

/*
======================= addEdge(int u, int v) =======================

	Adiciona uma aresta ou arco entre o vertice de origem u e o de chegada v.
	
	Parametros:
	
	int u -> Inteiro representando o id do vertice de origem.
	int v -> Inteiro representando o id do vertice de chegada.
*/
void Graph::addEdge(int u, int v, int weight){
	Vertex *itr = adjList;
	Vertex *dest = NULL;
	
	while(itr->id != u){
		if(itr->id == v){
			dest = itr;
		}
		itr = itr->next;
	}
	
	if(dest == NULL){
		Vertex *find = itr;

		while(find != NULL && find->id != v){
			find = find->next;
		} 
		cout << find->id << endl;
		if(find != NULL) dest = find; else cout << "Vertice nao existe" << endl;
	}
	
	itr->degree++;
	
	Edge *eItr = itr->adjL;
	
	if(itr->adjL != NULL){
		Edge *new_edge = new Edge(dest, weight);
		new_edge->next = eItr->next;
		eItr->next = new_edge;
	}else itr->adjL = new Edge(dest, weight);

	nE++;	
	
	if(!isOriented){
		dest = itr;
		itr = adjList;
	
		while(itr->id != v){
			itr = itr->next;
		}
		
		itr->degree++;
		
		Edge *eItr = itr->adjL;

		if(itr->adjL != NULL){
			Edge *new_edge = new Edge(dest, weight);
			new_edge->next = eItr->next;
			eItr->next = new_edge;	
		}else{
			itr->adjL = new Edge(dest, weight);
		}

		nE++;
	}
}

/*
======================= addVertex(int v) =======================	
	Adiciona um vértice v ao grafo.
	
	Parametros:
	
 	int v -> Inteiro representando o id do vertice. 
*/
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

/*
======================= auxDeleteEdge(int u, int v) =======================
	Função auxiliar da deleteEdge.
	
	Parametros:
	
	int u -> Inteiro representando o id do vertice de origem.
	int v -> Inteiro representando o id do vertice de chegada.
*/
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

/*
======================= deleteEdge(int u, int v) =======================
	Remove uma aresta ou arco entre o vertice de origem u e o de chegada v.
	
	Parametros:
	
	int u -> Inteiro representando o id do vertice de origem.
	int v -> Inteiro representando o id do vertice de chegada.
*/
void Graph::deleteEdge(int u, int v){
	this->auxDeleteEdge(u, v);
	
	if(!isOriented){
		this->auxDeleteEdge(v, u);
	}	
}

Edge* Graph::getAdjacents(int v){
	Vertex *itr = adjList;
	
	while(itr->id != v){
		itr = itr->next;
	}
	
	return itr->adjL;
}

/*
======================= removeVertex(int v) =======================
	Remove um vertice e suas ligacoes do grafo.
	
	Parametros:
	
	int v -> id do vertice v.
*/

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
		
		while(!stck.empty()){
			Edge *temp1 = stck.top();
			int id = temp1->id;	
			this->deleteEdge(id, v);	
			stck.pop();
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

	Vertex *temp = var->next;
	
	prev->next = temp;
	var = temp;
}

/*
======================= isRegular() =======================
	Verifica se o grafo é k-regular, caso seja, retorna 
o valor de k.
	Um grafo k-regular  é um grafo G = (V,E), tal que, para
todo v pertencente a V, d(v) = k. 
*/
int Graph::isRegular(){
	Vertex *itr = adjList;
	int degree = adjList->degree;
	
	while(itr != NULL && itr->degree == degree){
		itr = itr->next;
	}
	
	return (itr == NULL)?degree:0;
}

/*
======================= isComplete() =======================
	Verifica se o grafo é completo (Kq).
	Um grafo G = (V,E) é dito completo se, para todo v pertencente
a V, d(v) = nV - 1. Sendo nV o numero de vertices em G.
	Kq  um grafo completo de ordem q.
*/
bool Graph::isComplete(){
	Vertex *itr = adjList;
	
	while(itr != NULL && itr->degree == nV - 1){
		itr = itr->next;
	}
	
	return (itr == NULL);
}

/*
======================= geraCompleto() =======================
	Funcao para gerar um grafo completo.
*/
void Graph::geraCompleto(){
	Vertex *itr = adjList;
	
	while(itr != NULL){
		for(int i = 0; i < nV; i++){
			if(i != itr->id){
				this->addEdge(itr->id, i, 0);	
			}
		}
		itr = itr->next;
	}
}

/*
======================= print() =======================
	Funcao para imprimir a lista de adjacencias do grafo.
*/
void Graph::print(){
	Vertex *itr = adjList;
	while(itr->next != NULL){
		cout << itr->id << ": ";
		Edge *itr1 = itr->adjL;
		
		while(itr1 != NULL){
			cout << "(" << itr1->id <<", " << itr1->weight << ")";
			if(itr1->next != NULL) cout << "->"; else cout << ";";
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
}

Graph::~Graph(){
	nV = 0;
	nE = 0;
	delete adjList;
	adjList = NULL;
	cout << "\nGraph deleted successfully!" << endl;
}
