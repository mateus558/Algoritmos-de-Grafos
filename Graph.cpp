#include "Graph.h"

int Graph::removed;
int Graph::ins;

/*
======================= Graph() =======================
	Construtor padrao do grafo, inicializa um grafo vazio.
	
*/
Graph::Graph(){
	this->nV = 0;
	this->nE = 0;
	this->degree = -1;
	removed = 0;
	isOriented = false;
	adjList->head = new Vertex;
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
	isOriented = isOriented;
	nV = V;
	nE = 0;
	degree = -1;
	removed = 0;
	ins = 0;
	adjList = new AdjacencyList;

	for(int i = 0; i < V; i++){	
		adjList->push_front(i);
	}
	
	int mid = (adjList->head->id + adjList->tail->id)/2;
	
	Vertex *middle = adjList->head;
	
	while(middle->id != mid-1){
		middle = middle->next;
	}	
	
	adjList->middle = middle;
}

int Graph::size(){
	return (isOriented)?nE:nE/2;
}

/*
======================= getMaxGraphDegree() =======================
	Retorna o grau do grafo.

	O grau de um grafo G = (V,E), é o grau máximo do conjunto V de
vértices pertencentes a G.

*/
int Graph::getMaxGraphDegree(){
	Vertex *itr = adjList->head;
	int maior = itr->degree;
	
	if(itr == NULL) return -1;
	
	while(itr != NULL){
		if(itr->degree > maior)
			maior = itr->degree;
			
		itr = itr->next;
	}
	
	return maior;
}

Vertex* Graph::getBegin(int v){
	Vertex *itr;
	
	if(adjList->head){
		if(v >= adjList->head->id && v < adjList->middle->id){
			itr = adjList->head;
		}else if(v >= adjList->middle->id && v < adjList->tail->id){
			itr = adjList->middle;
		}else itr = adjList->tail;
	}else itr = NULL;
	
	return itr;
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
	Vertex *itr = adjList->head;
	
	while(itr != NULL && itr->id != v){
		itr = itr->next;
	}
	
	return (itr == NULL)?-1:itr->degree;
}

bool Graph::isAdjacent(int u, int v){
	int dest;
	int ori;
	
	if(!isOriented){
		dest = (u < v)?u:v;
	        ori = (dest == u)?v:u;
	}else{
		dest = u;
		ori = v;
	}	
	
	Vertex *itr = getBegin(u);
	
	while(itr->id != dest){
		itr = itr->next;
	}
	
	Edge *eItr = itr->adjL;
	
	while(eItr->id != ori){
		eItr = eItr->next;	
	}
	
	return (eItr->id == ori);
}

/*
======================= addEdge(int u, int v) =======================

	Adiciona uma aresta ou arco entre o vertice de origem u e o de chegada v.
	
	Parametros:
	
	int u -> Inteiro representando o id do vertice de origem.
	int v -> Inteiro representando o id do vertice de chegada.
*/

void Graph::addEdge(int u, int v, int weight){
	Vertex *itr = NULL;
	PairV dests = make_pair(itr, itr);
	dests = adjList->addEdge(dests, u, v, weight, 0);

	//Se o grafo nao for orientado, repetir processo anterior para o vertice de destino
	if(!isOriented){
		dests = adjList->addEdge(dests, v, u, weight, 1);
	}
	
	nE++;
}

/*
======================= addVertex(int v) =======================	
	Adiciona um vértice v ao grafo.
	
	Parametros:
	
 	int v -> Inteiro representando o id do vertice. 
*/
void Graph::addVertex(int v){
	Vertex *itr = getBegin(v);
	
	//Verifica se o vertice a ser inserido esta proxima do inicio, do meio ou do fim da lista de adjacencias
	
	
	//Caso o vertice tenha id menor que o ultimo da lista inserir no final
	if(itr != adjList->tail){
		Vertex *dad = itr;
	
		while(itr != NULL && itr->id <= v){
			dad = itr;
			itr = itr->next;
		}
	
		Vertex *new_vertex = new Vertex(v);

		new_vertex->next = itr;
		dad->next = new_vertex;
	}else adjList->push_front(v);
	
	//Avanca o ponteiro para o meio da lista de adjacencia
	if(adjList->middle->next && ins%2 == 0) adjList->middle = adjList->middle->next; 
	ins++;
	
	nV++;
}

/*
======================= deleteEdge(int u, int v) =======================
	Remove uma aresta ou arco entre o vertice de origem u e o de chegada v.
	
	Parametros:
	
	int u -> Inteiro representando o id do vertice de origem.
	int v -> Inteiro representando o id do vertice de chegada.
*/
void Graph::deleteEdge(int u, int v){
	adjList->deleteEdge(u, v);
	
	if(!isOriented){
		adjList->deleteEdge(v, u);
	}	
	
	nE--;
}

vector<Edge*> Graph::getAdjacents(int v){
	Vertex *itr = adjList->head;
	vector<Edge*> adja;
	
	while(itr->id != v){
		itr = itr->next;
	}
	
	Edge *adj = itr->adjL;
	
	while(adj != NULL){
		adja.push_back(adj);
		adj = adj->next;
	}
	
	return adja;
}

/*
======================= removeVertex(int v) =======================
	Remove um vertice e suas ligacoes do grafo.
	
	Parametros:
	
	int v -> id do vertice v.
*/

void Graph::removeVertex(int v){
	removed++;
	Vertex *itr = getBegin(v);;
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
		itr = getBegin(v);
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
	temp->prev = prev;
	prev->next = temp;
	var = temp;
	if(adjList->middle->prev && removed%2 == 0) adjList->middle = adjList->middle->prev; 
	
	nV--;
}

/*
======================= isRegular() =======================
	Verifica se o grafo é k-regular, caso seja, retorna 
o valor de k.
	Um grafo k-regular  é um grafo G = (V,E), tal que, para
todo v pertencente a V, d(v) = k. 
*/
int Graph::isRegular(){
	Vertex *itr = adjList->head;
	int degree = adjList->head->degree;
	
	while(itr != NULL && itr->degree == degree){
		itr = itr->next;
	}
	
	return (itr == NULL)?degree:-1;
}

/*
======================= isComplete() =======================
	Verifica se o grafo é completo (Kq).
	Um grafo G = (V,E) é dito completo se, para todo v pertencente
a V, d(v) = nV - 1. Sendo nV o numero de vertices em G.
	Kq  um grafo completo de ordem q.
*/
bool Graph::isComplete(){
	Vertex *itr = adjList->head;
	
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
	Vertex *itr = adjList->head;
	
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
	Vertex *itr = adjList->head;
	while(itr != adjList->tail->next){
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
	
	cout << adjList->head->id << " " << adjList->tail->id  << " " << adjList->middle->id<< endl; 
}

Graph::~Graph(){
	nV = 0;
	nE = 0;
	delete adjList->head;
	adjList->head = NULL;
	cout << "\nGraph deleted successfully!" << endl;
}
