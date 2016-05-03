#include "Graph.h"
#include <algorithm>

int Graph::removed;
int Graph::ins;

/*
======================= Graph() =======================
	Construtor padrao do grafo, inicializa um grafo vazio.
	
*/
Graph::Graph(){
	nV = 0;
	nE = 0;
	degree = -1;
	removed = 0;
	maxId = 0;
	isOriented = false;
	adjList = new AdjacencyList;

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
		adjList->push_back(i);
	}
	
	maxId = V - 1;
}

bool Graph::ehOriented(vector<pair<int,int> > edges){
	vector<pair<int,int> >::iterator itr, itr1;

	for(itr = edges.begin(); itr != edges.end(); itr++){
		for(itr1 = edges.begin(); itr1 != edges.end(); itr1++){
			if(((*itr).first == (*itr1).second) && ((*itr).second == (*itr1).first)){
				return false;
			}
		}
	}
	return true;
}

int Graph::size(){
	return (isOriented)?nE:nE/2;
}

void Graph::DFS(){
	//Marcar todos vertices como nao visitados
	bool* isVisited = new bool[maxId];
	for(int i = 0; i < maxId; isVisited[i++] = false);
	
	for(int i = 0; i <= maxId; i++){
		if(!isVisited[i]){
			DFSUtil(i, isVisited);
		}
	}
}

void Graph::DFSUtil(int id, bool* isVisited){
	//Pilha para o DFS
	stack<Vertex*> stack;
	
	//Marcar o primeiro vertice como visitado e colocar na pilha
	Vertex* v = getBegin(id);
	
	while(v != NULL && v->id != id){
		v = v->next;
	}
	if(v == NULL) return;
	
	isVisited[id] = true;
	stack.push(v);
	
	cout << id << " ";
	while(!stack.empty()){
		Vertex *u = stack.top();
		stack.pop();

		for(Edge* itr = u->adjL; itr != NULL; itr = itr->next){
			int uId = itr->dest->id;
			
			if(!isVisited[uId]){
				isVisited[uId] = true;
				cout << uId <<" ";
				stack.push(itr->dest);
			}
		} 
	}
}

bool Graph::isConnected(){
	vector<bool> isVisited(maxId, false);
	
	stack<Vertex*> stack;	
	Vertex* v = adjList->head;
	int i = 1;
	
	isVisited[adjList->head->id] = true;
	stack.push(v);
	
	while(!stack.empty()){
		Vertex *u = stack.top();
		Vertex *pred = u;
		stack.pop();

		for(Edge* itr = u->adjL; itr != NULL; itr = itr->next){
			int uId = itr->dest->id;
			
			if(!isVisited[uId] && itr->dest != pred){
				isVisited[uId] = true;
				i++;
				stack.push(itr->dest);
			}
		} 
	}

	return (i == nV);
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
		if(v >= adjList->head->id){
			itr = adjList->head;
		}else if(v >= adjList->tail->id) itr = adjList->tail;
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
		dest = min(u,v);
	        ori = (dest == u)?v:u;
	}else{
		dest = u;
		ori = v;
	}	
	
	Vertex *itr = getBegin(dest);

	while(itr->id != dest){
		itr = itr->next;
	}

	Edge *eItr = itr->adjL;
	
	while(eItr != NULL && eItr->id != ori){
		eItr = eItr->next;	
	}

	return (eItr != NULL && eItr->id == ori);
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
	cout << "poop1" << endl;
	dests = adjList->addEdge(dests, u, v, weight, 0);
	
	//Se o grafo nao for orientado, repetir processo anterior para o vertice de destino
	if(!isOriented){
		dests = adjList->addEdge(dests, v, u, weight, 1);
	}
	
	nE++;
}

void Graph::addEdge(int u, int v){
	Vertex *itr = NULL;
	PairV dests = make_pair(itr, itr);
	dests = adjList->addEdge(dests, u, v, -1, 0);
	cout << "cu" << endl;
	//Se o grafo nao for orientado, repetir processo anterior para o vertice de destino
	if(!isOriented){
		dests = adjList->addEdge(dests, v, u, -1, 1);
	}
	
	nE++;
}

bool Graph::exist(int v){
	Vertex *itr = adjList->head;
	//cout << adjList->tail->next->id << endl;
	if(itr != NULL){
		while(itr != adjList->tail && itr->id != v){
			itr = itr->next;
		}
	}else return false;
	
	return (itr != adjList->tail->next);	
}

/*
======================= addVertex(int v) =======================	
	Adiciona um vértice v ao grafo.
	
	Parametros:
	
 	int v -> Inteiro representando o id do vertice. 
*/
void Graph::addVertex(int v){
	cout << v << " " << !exist(v) <<endl;
	if(!exist(v)){
		if(nV > 0){
			//Verifica se o vertice a ser inserido esta proxima do inicio, do meio ou do fim da lista de adjacencias
			Vertex *itr;
			Vertex *new_vertex = new Vertex(v);
			maxId = (v > maxId)?v:maxId;
			nV++;
	
			if(v >= adjList->head->id && v <= adjList->tail->id){
				cout << "poop" << endl;
				for(itr = getBegin(v); itr != adjList->tail->next && itr->id <= v; itr = itr->next);
			
			}else if(v >= adjList->tail->id){
				adjList->push_back(v);
				return;
			}else if(v < adjList->head->id){
				adjList->push_front(v);
				return;
			}	
	
			if(itr->id >= v){
				itr->prev->next = new_vertex;
				new_vertex->prev = itr->prev;
				new_vertex->next = itr;
				itr->prev = new_vertex;
			}
		}else{
			adjList->push_front(v);
		}
	}else 	cout << "poop1" << endl;

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
	while(itr != adjList->tail->next && itr->id != v){
		prev = itr;
		itr = itr->next;
	}

	maxId = (v == maxId)?itr->prev->id:maxId;

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

void Graph::isBipartiteUtil(int id, bool* isVisited, int& it, int8_t* conj, bool& isBi){
	//Pilha para o DFS
	stack<Vertex*> stack;
	
	//Marcar o primeiro vertice como visitado e colocar na pilha
	Vertex* v = getBegin(id);
	
	while(v != NULL && v->id != id){
		v = v->next;
	}
	
	if(v == NULL) return;

	isVisited[id] = true;
	conj[id] = it%2;
	it++;
	stack.push(v);
	
	while(!stack.empty()){
		Vertex *u = stack.top();
		stack.pop();
		
		for(Edge *itr = u->adjL; itr != NULL; itr = itr->next){
			if(!isVisited[itr->id]){
				isVisited[itr->id] = true;
				conj[itr->id] = it%2;
				it++;
				stack.push(itr->dest);
			}else if(itr->id != id && conj[id] == conj[itr->id]){
				isBi = false;
				return;
			}
		}
	}
}

bool Graph::isBipartite(){
	bool* isVisited = new bool[maxId];
	bool isBi = true;
	int8_t* conj = new int8_t[maxId];
	int i = 2;
	
	for(int i = 0; i < maxId; isVisited[i++] = false);
	for(int i = 0; i < maxId; conj[i++] = 0);
	
	for(int v = 0; v < maxId; v++){
		if(!isVisited[v]){
			isBipartiteUtil(v, isVisited, i, conj, isBi);
		}
	}	
	
	return isBi;
}

Graph* Graph::inducedGraph(vector<pair<int, int> > edges){
	vector<pair<int, int> >::iterator itr;
	Graph* grafo = new Graph;
			
	for(itr = edges.begin(); itr != edges.end(); itr++){
		grafo->addVertex((*itr).first);
		grafo->addVertex((*itr).second);
									cout << "dsk" <<endl;
		grafo->addEdge((*itr).first, (*itr).second);
	}
	
	return grafo;
}

/*
======================= print() =======================
	Funcao para imprimir a lista de adjacencias do grafo.
*/
string Graph::print(){
	string printed;
	ostringstream stream;
	Vertex *itr = adjList->head;
	stream << '\n';
	while(itr != adjList->tail->next){
		stream << itr->id << ": ";
		Edge *itr1 = itr->adjL;
		
		while(itr1 != NULL){
			stream << "(" << itr1->id <<", " << itr1->weight << ")";
			if(itr1->next != NULL) stream << "->"; else stream << ";";
			itr1 = itr1->next;
		}
		
		stream << '\n';
		itr = itr->next;
	}
	stream << '\n';
	
	return stream.str();	
}

Graph::~Graph(){
	nV = 0;
	nE = 0;
	delete adjList->head;
	adjList->head = NULL;
	cout << "\nGraph deleted successfully!" << endl;
}
