#include "Graph.h"

struct comparator{
	bool operator()(const Vertex* u, const Vertex* v){
		return u->d > v->d;
	} 
};

struct edgeComp{
	bool operator()(const Edge* u, const Edge* v){
		return u->weight > v->weight;
	} 
};

/*
======================= Graph() =======================
	Construtor padrao do grafo, inicializa um grafo vazio.
	
*/
Graph::Graph(){
	nV = 0;
	nE = 0;
	degree = -1;
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
	this->isOriented = isOriented;
	cout << isOriented << endl;
	nV = V;
	nE = 0;
	degree = -1;
	adjList = new AdjacencyList;
	dist = vector<int>(V, INF);
	for(int i = 0; i < V; i++){	
		adjList->push_back(i);
	}
	
	maxId = V - 1;
}

/*
======================= ehOriented() =======================
	Diz se o grafo eh orientado.
	
	Parametros:
	
	vector<pair<int,int> > edges -> conjunto de arestas.
*/
bool Graph::ehOriented(vector<pair<int,int> > edges){
	vector<pair<int,int> >::iterator itr, itr1;

	for(itr = edges.begin(); itr != edges.end(); itr++){
		for(itr1 = edges.begin(); itr1 != edges.end(); itr1++){
			if(((*itr).first == (*itr1).second) && ((*itr).second == (*itr1).first)){
				return true;
			}
		}
	}
	return false;
}

list<Vertex*> Graph::directTransitiveClosure(int v){

}

list<Vertex*> Graph::indirectTransitiveClosure(int v){

}

AdjacencyList* Graph::transposeGraph(){

}

/*
======================= size() =======================
	Retorna o tamanho do grafo (cardinalidade do conjunto de arestas).
	
*/
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

/*
======================= isConnected() =======================
	Diz se o grafo eh conexo.
	Um grafo eh conexo se existe um caminho para todos vertices a partir de qualquer origem.

*/
bool Graph::isConnected(){
	//Inicializa vetor de visita com tamanho do vertice de maior Id com false
	vector<bool> isVisited(maxId, false);
	
	stack<Vertex*> stack;	//Cria pilha para a busca em profundidade	
	Vertex* v = adjList->head;	//Seta o primeiro vertice a ser visitado como o primeiro da lista de adjacencia
	int i = 1;	//Inicializa o numero de vertices visitados como 1
	isVisited[adjList->head->id] = true;	//Seta o primeiro vertice como visitado
	stack.push(v);	//Coloca v na pilha para explorar seus adjacentes
	
	while(!stack.empty()){ //Enquanto a pilha nao estiver vazia
		Vertex *u = stack.top();	//Pega o vertice do topo da pilha
		Vertex *pred = u;	//Seta ele como predecessor dos adjacentes
		stack.pop();	//Retira u da pilha

		for(Edge* itr = u->adjL; itr != NULL; itr = itr->next){	//Iteracao dos adjacentes
			int uId = itr->dest->id;	//id da aresta
			
			if(!isVisited[uId] && itr->dest != pred){	//Se o vertice da aresta nao foi visitado e eh diferente de seu predecessor
				isVisited[uId] = true; 	//Seta u como visitado
				i++;	//Incrementa o numero de visitados
				stack.push(itr->dest);	//Coloca na pilha para visitar seus adjacentes
			}
		} 
	}

	return (i == nV);	//Se foi possivel visitar todos vertices a partir do vertice selecionado arbitrariamente, entao o grafo eh conexo
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

Matrix Graph::getWeightMatrix(){
	Vertex *itr = adjList->head;
	Matrix W = Matrix(nV, vector<int>(nV));
	Edge *eitr;
	int u, v;
	
	for(; itr != NULL; itr = itr->next){
		u = itr->id;
		eitr = itr->adjL;
		
		for(; eitr != NULL; eitr = eitr->next){
			v = eitr->id;
			W[u][v] = eitr->weight;
		}
	}
	
	for(int i = 0; i < nV; i++){
		for(int j = 0; j < nV; j++){
			if(W[i][j] == 0){
				if(i != j){
					W[i][j] = INF;
				}else W[i][j] = INF;
			}
		}
	}
	
	return W;
}

vector<Vertex*> Graph::initializeSingleSource(vector<Vertex*> minHeap, int i){
	Vertex *itr = adjList->head;
	
	while(itr != NULL){
		if(itr->id != i)
			itr->d = INF;
		else itr->d = 0;
		itr->dad = NULL;
		minHeap.push_back(itr);
		push_heap(minHeap.begin(), minHeap.end(), comparator());
		itr = itr->next;
	}
	
	return minHeap;
}

vector<Vertex*> Graph::relax(Edge *v, Vertex *u, vector<Vertex*> minHeap, int *dis, int k){
	if(v->dest->d > u->d + v->weight){
		v->dest->d = u->d + v->weight;
		v->dest->dad = u;
		make_heap(minHeap.begin(), minHeap.end(), comparator());
		if(v->id == k){
			*dis = v->dest->d;
		}
	}
	
	return minHeap;
}

int Graph::djkstra(int i, int k){
	int dis = 0;
	
	vector<Vertex*> minHeap;
	vector<Vertex*> S;
	
	minHeap = initializeSingleSource(minHeap, i);	
	make_heap(minHeap.begin(), minHeap.end(), comparator());

	while(!minHeap.empty()){
		Vertex *u = minHeap.front();
		S.push_back(u);
		pop_heap(minHeap.begin(), minHeap.end(), comparator());
		minHeap.pop_back();
		
		for(Edge *v = u->adjL; v != NULL; v = v->next){
			minHeap = relax(v, u, minHeap, &dis, k);
		}
	}

	return dis;
}

int Graph::MSTKruskal(){
	Union_Find UF(nV);
	
	priority_queue<Edge*, vector<Edge*>, edgeComp> minHeap;
	
	int dist = 0;
	
	Vertex* itr = adjList->head;
	
	for(; itr != NULL; itr = itr->next){
		Edge* eitr;
		Edge* ant = NULL;
		for(eitr = itr->adjL; eitr != NULL; eitr = eitr->next){
			minHeap.push(eitr);
			ant = eitr;
		}
	}
	
	while(!minHeap.empty()){
		Edge* e = minHeap.top();
		minHeap.pop();

		if(!UF.find(e->ini->id, e->id)){
			dist += e->weight;
			UF.unite(e->ini->id, e->id);
		}
	}

	return dist;
}

int Graph::MSTPrim(){
	srand(time(NULL));
	
	int dis(0), i(0);
	vector<Vertex*> minHeap;
	vector<bool> inMST(nV, false);
	
	minHeap = initializeSingleSource(minHeap, i);	
	make_heap(minHeap.begin(), minHeap.end(), comparator());
	
	while(!minHeap.empty()){
		Vertex *u = minHeap.front();
		
		pop_heap(minHeap.begin(), minHeap.end(), comparator());
		minHeap.pop_back();
		inMST[u->id] = true;
		dis += u->d;
		
		for(Edge *v = u->adjL; v != NULL; v = v->next){
			if(!inMST[v->id] && v->weight < v->dest->d){
				v->dest->d = v->weight;
				v->dest->dad = u;
				make_heap(minHeap.begin(), minHeap.end(), comparator());
			}
		}
	}
	
	return dis;
}

Matrix Graph::floydWarshall(Matrix W){
	int n = nV;

	for(int k = 1; k < n; k++){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if (W[i][k] + W[k][j] < W[i][j])			            						W[i][j] = W[i][k] + W[k][j];
			}
		}
	}
	return W;
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

/*
 ======================= isAdjacent(int u, int v) =======================

 	Verifica se dois vertices sao adjacentes.
 
 	Parametros:
	
 	int u -> vertice de origem.
	int v -> vertice de destino.
*/
bool Graph::isAdjacent(int u, int v){
	int dest = u;
	int ori = v;
	
	if(!isOriented){
		dest = (u < v)?u:v;
	        ori = (dest == u)?v:u;
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
	dests = adjList->addEdge(dests, u, v, weight, 0);
	
	//Se o grafo nao for orientado, repetir processo anterior para o vertice de destino
	if(!isOriented){
		dests = adjList->addEdge(dests, v, u, weight, 1);
		nE++;
	}
	
	nE++;
}

void Graph::addEdge(int u, int v){
	Vertex *itr = NULL;
	PairV dests = make_pair(itr, itr);
	dests = adjList->addEdge(dests, u, v, -1, 0);
	//Se o grafo nao for orientado, repetir processo anterior para o vertice de destino
	if(!isOriented){
		dests = adjList->addEdge(dests, u, v, -1, 1);
		nE++;
	}
	
	nE++;
}

/*
======================= exist(int v) =======================	
	Verifica se um vertice v existe no grafo.	
	
	Parametros:
	
 	int v -> Inteiro representando o id do vertice. 
*/
bool Graph::exist(int v){
	Vertex *itr = adjList->head;

	if(itr != NULL){
		while(itr != adjList->tail && itr->id != v){
			if(itr->id == v){
				return true;
			}
			itr = itr->next;
		}
	}
	
	return false;
}

/*
======================= addVertex(int v) =======================	
	Adiciona um vértice v ao grafo.
	
	Parametros:
	
 	int v -> Inteiro representando o id do vertice. 
*/
void Graph::addVertex(int v){
	if(!exist(v)){
		if(nV > 0){
			//Verifica se o vertice a ser inserido esta proxima do inicio, do meio ou do fim da lista de adjacencias		
			Vertex *itr;
			Vertex *new_vertex = new Vertex(v);
			maxId = (v > maxId)?v:maxId;
			
			if(v >= adjList->head->id && v <= adjList->tail->id){
				for(itr = getBegin(v); itr != adjList->tail->next && itr->id <= v; itr = itr->next);
			
			}else if(v >= adjList->tail->id){
				adjList->push_back(v);
				nV++;
				return;
			}else if(v <= adjList->head->id){
				adjList->push_front(v);
				nV++;
				return;
			}	
	
			if(itr->id >= v){
				new_vertex->prev = itr->prev;
				new_vertex->prev->next = new_vertex;
				new_vertex->next = itr;
				itr->prev = new_vertex;
			}
			nV++;
		}else{
			nV++;
			adjList->push_front(v);
		}
	}else{
		cout << "\nVertice ja existe!\n";
		return;
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
	adjList->deleteEdge(u, v);
	
	if(!isOriented){
		adjList->deleteEdge(v, u);
	}	
	
	nE--;
}

/*
======================= getAdjacents(int v) =======================
	Revorna um vetor deinteiros representando os vertices adjacentes.
	
	Parametros:
	
	int v -> Inteiro representando o id do vertice.
*/
vector<Edge*> Graph::getAdjacents(int v){
	Vertex *itr = adjList->head;
	vector<Edge*> adja;
	
	while(itr != adjList->tail->next && itr->id != v){
		itr = itr->next;
	}
	
	if(itr == adjList->tail->next){
		return adja;
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
	Vertex *itr = getBegin(v);;
	Vertex *prev = itr;
	
	while(itr != adjList->tail->next && itr->id != v){
		prev = itr;
		itr = itr->next;
	}
	
	if(itr == adjList->tail->next){
		cout << "vertice nao existe." << endl;
		return;
	}
		
	maxId = (v == maxId)?itr->prev->id:maxId;

	Edge *itrE = itr->adjL;
	stack<Edge*> stck;	
	Vertex *del = itr;
	
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
	
	if(adjList->head == NULL || del == NULL){
		return;
	}
	
	if(del == adjList->head){
		adjList->head = del->next;
	}
	
	if(del == adjList->tail){
		adjList->tail = del->next;
	}
	
	if(del->next != NULL){
		del->next->prev = del->prev;
	}
	
	if(del->prev != NULL){
		del->prev->next = del->next;
	}
	delete del;
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
======================= isBipartiteUtil(Vertex *v, bool* isVisited, int& it, int* conj, bool& isBi) =======================
	Verifica se o grafo eh bipartido ou nao atraves do DFS.
	
	Parametros:
	
	Vertex *v -> vertice v.
	bool* isVisited -> vetor para marcar e verificar se os vertices foram visitados.
	int& it -> iteracao atual.
	int8_t* conj -> marca a qual conjunto de vertices so vertices foram colocados.
	bool& isBi -> diz se o grafo e ou nao bipartido.
*/
void Graph::isBipartiteUtil(Vertex *v, bool* isVisited, int& it, int* conj, bool& isBi){
	//Pilha para o DFS
	stack<Vertex*> stack;
	
	//Marcar o primeiro vertice como visitado e colocar na pilha
	isVisited[v->id] = true;
	conj[v->id] = it%2;
	stack.push(v);
	
	while(!stack.empty()){
		Vertex *u = stack.top();
		stack.pop();
		it++;
		for(Edge *itr = u->adjL; itr != NULL; itr = itr->next){
			if(conj[itr->id] == -1){
			
				isVisited[itr->id] = true;
				conj[itr->id] = it%2;
				stack.push(itr->dest);
			
			}else if(u->id != itr->id && conj[u->id] == conj[itr->id]){
				isBi = false;
				return;
			}
		}
	}
}

/*
======================= isBipartite() =======================
	Verifica se o grafo eh bipartido ou nao atraves do DFS.
*/
bool Graph::isBipartite(){
	bool* isVisited = new bool[maxId];
	bool isBi = true;
	int* conj = new int[maxId];
	int i = 2;
	
	for(int i = 0; i < maxId; isVisited[i++] = false);
	for(int i = 0; i < maxId; conj[i++] = -1);
	
	for(Vertex *v = adjList->head; v != adjList->tail->next; v = v->next){
		if(conj[v->id] == -1){
			isBipartiteUtil(v, isVisited, i, conj, isBi);
			if(!isBi) return false;
		}
	}	
	
	return isBi;
}

/*
======================= countComponents(Vertex *w, int &n, int* components) =======================
	Conta quantas componentes conexas tem no grafo através do DFS.
	
	Parametros:
	
	Vertex *w -> vertice fonte w.
	int &n -> Contador de componentes conexas.
	int* components -> vetor que diz a qual componente conexa certo vertice pertence.
*/
void Graph::countComponents(Vertex *w, int &n, int* components){
	stack<Vertex*> stack;
	components[w->id] = n;
	stack.push(w);

	while(!stack.empty()){
		Vertex *u = stack.top();
		Vertex *pred = u;
		stack.pop();
		
		for(Edge* itr = u->adjL; itr != NULL; itr = itr->next){
			int v = itr->dest->id;

			if(components[v] == 0 && v != pred->id){
				components[v] = n;
				stack.push(itr->dest);
			}
		}
	}
}

/*
======================= nConnectedComponents() =======================
	Retorna a quantidade de componentes conexas do grafo.
*/
int Graph::nConnectedComponents(){
	int* components = new int[maxId];
	int n = 0;
	
	for(int i = 0; i < maxId; components[i++] = 0);

	for(Vertex *itr = adjList->head; itr != adjList->tail->next; itr = itr->next){
		if(components[itr->id] == 0){
			n++;
			countComponents(itr, n, components);	
		}
	}

	return n;
}

/*
======================= isArticulation(int v) =======================
	Verifica se o vertice v eh de articulacao.
	
	Parametros:
	
	int v -> vertice v.
*/
bool Graph::isArticulation(int v){
	stack<pair<int, int> > stack;
	Vertex* itr;
	
	for(itr = getBegin(v); itr != adjList->tail->next && itr->id != v; itr = itr->next);
	
	if(itr == adjList->tail->next){
		cout << "Vertice invalido!" << endl;
		return false;
	}	 
	
	for(Edge* adj = itr->adjL; adj != NULL;){
		stack.push(make_pair(adj->id, adj->weight));
		adj = adj->next;
	}	
	
	int nConPrev = nConnectedComponents();
	
	removeVertex(v);
	
	int nCon = nConnectedComponents();
	
	addVertex(v);

	while(!stack.empty()){
		pair<int, int> u = stack.top();
		stack.pop();
		
		addEdge(v, u.first, u.second);
	}
	
	return (nCon > nConPrev);
}

/*
======================= complementaryGraph() =======================
	Retorna o grafo complementar a G.
*/
Graph* Graph::complementaryGraph(){
	Graph* grafo = new Graph;
	
	for(Vertex* itr = adjList->head; itr != adjList->tail->next; itr = itr->next){
		grafo->addVertex(itr->id);
	}
	
	for(Vertex* itr = adjList->head; itr != adjList->tail->next; itr = itr->next){
		for(Vertex* itr1 = adjList->head; itr1 != adjList->tail->next; itr1 = itr1->next){
			
			if(itr1->id != itr->id){
				Edge* adj;

				for(adj = itr->adjL; adj != NULL && adj->id != itr1->id; adj = adj->next);
				
				if(!adj){
					grafo->addEdge(itr->id, itr1->id);
				}
			}
		}
	}
	
	return grafo;
}

/*
======================= inducedGraph(vector<int> V, Graph* G) =======================
	Retorna o grafo induzido pelo conjunto de vertices V' que eh subconjunto do conjunto de vertices V do grafo G.
	
	Parametros:
	
	vector<int> V -> conjunto de vertices V' pertencente ao conjunto V do grafo G.
	Graph* G -> grafo G = (V,E).
*/
AdjacencyList* Graph::inducedGraph(vector<int> V, Graph* G){
	vector<int>::iterator itr;
	AdjacencyList* grafo = new AdjacencyList;
	vector<vector<Edge*> > edges;
	
	for(itr = V.begin(); itr != V.end(); itr++){
		edges.push_back(G->getAdjacents((*itr)));
		grafo->push_back((*itr));
	}	
	
	Vertex *itr0 = grafo->head;
	
	if(V.size() == 0){
		return NULL;
	}	

	for(int j = 0; itr0 != grafo->tail->next; itr0 = itr0->next, j++){
		int u = itr0->id;
		
		for(int i = 0; i < edges[j].size(); i++){
			bool add = false;
			
			for(int k = 0; k < V.size(); k++){
				if(V[k] == edges[j][i]->id)
					add = true;
			}
				
			if(add){
				Edge* eItr = itr0->adjL;
				Edge* temp = itr0->adjL;
				
				itr0->adjL = new Edge(edges[j][i]->id, edges[j][i]->weight);
				itr0->adjL->next = temp; 
			}
		}
		
	}
	return grafo;
}

/*
======================= getWeight(int u, int v) =======================
	Retorna o peso da aresta (u, v).
	
	Parametros:
	
	int u -> vertice de origem.
	int v -> vertice de destino.
*/
int Graph::getWeight(int u, int v){
	Vertex* itr;
	
	for(itr = getBegin(u); itr != adjList->tail->next && itr->id != u; itr = itr->next);
	
	if(itr == adjList->tail->next){
		cerr << "Vertice nao existe." << endl; 
		return -1;
	}else if(itr->adjL != NULL && itr->adjL->weight == -1){
		return -2;
	}
	
	Edge *adj;
	
	for(adj = itr->adjL; adj != NULL && adj->id != v; adj = adj->next);
	
	return (adj == NULL)?-3:adj->weight;
}

/*
======================= isBridge(int u, int v) =======================
	Verifica se a aresta (u, v) eh uma ponte.
	
	Parametros:
	
	int u -> vertice de origem.
	int v -> vertice de destino.
*/
bool Graph::isBridge(int u, int v){
	int prevComp = nConnectedComponents();
	int w = getWeight(u,v);
	if(w == -1){
		cerr << "\nUm dos ou os dois vertices nao existe!" << endl;
		return false;
	}
	if(w == -3){
		cerr << "\naresta nao existe." << endl;
		return false;
	}
	
	deleteEdge(u, v);
	
	int posComp = nConnectedComponents();
	
	if(w != -2){
		addEdge(u, v, w);
	}else addEdge(u, v);
	
	return (posComp > prevComp);
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
	
	for(;itr != adjList->tail->next; itr = itr->next){	//Percorre vertices
		stream << itr->id << ": ";
		
		Edge *itr1 = itr->adjL;
		
		for(;itr1 != NULL; itr1 = itr1->next){	//Percorre arestas
			stream << "(" << itr1->id <<", " << itr1->weight << ")";
			
			if(itr1->next != NULL) stream << "->"; else stream << ";";
		}
		
		stream << '\n';
	}
	
	stream << '\n';
	
	return stream.str();	
}

Graph::~Graph(){
	Vertex *itr = adjList->head;
	
	while(itr != adjList->tail->next){
		Edge *adj = itr->adjL;
		Vertex *delv = itr;
		while(adj != NULL){
			Edge *dela = adj;
			adj = adj->next;
			delete dela;
		}
		itr = itr->next;
		delete itr;
	}
	cout << "\nGraph deleted successfully!" << endl;
}
