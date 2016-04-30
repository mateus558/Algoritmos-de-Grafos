#include "Graph.h"
#include <limits>
#include <fstream>


using namespace std;

bool sair = false;

void clear(void);
int showMenu(void);
void executeOption(int, Graph*);
void waitUserAction(void);
Graph* populateWeightedGraph(string);
bool isOriented(vector<pair<int,int> >);

int main(int argc, char** argv){
	if(argc == 3){
		string fileName(argv[1]), output(argv[2]);
		
		Graph *grafo = populateWeightedGraph(fileName);

		clear();
		while(true){	
			if(sair){
				return 0;
			}
		
			int option = showMenu();
			
			executeOption(option, grafo);
			
			clear();
		}
		
	}else{
		cerr << "Run the program in the following format:" << endl;
		cerr << "./T1_201465559AC <input filename> <output filename>" << endl; 
	}
	
	return 0;
}

bool isOriented(vector<pair<int,int> > edges){
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

Graph* populateWeightedGraph(string fileName){
	ifstream in(fileName);
	int nV, ini, fim, weight;
	vector<int> weights;
	vector<pair<int,int> > edges;
	
	if(!in){
		cerr << "Arquivo nao pode ser aberto..." << endl;
		return 0;
	}
		
	in >> nV;
	
	while(in >> ini >> fim >> weight){
		edges.push_back(make_pair(ini,fim));
		weights.push_back(weight);
	}

	Graph *grafo = new Graph(nV, isOriented(edges));

	for(int i = 0; i < edges.size(); i++){
		grafo->addEdge(edges[i].first, edges[i].second, weights[i]);
	}
	
	return grafo;
}

void clear(void){
	system("clear");
}

void waitUserAction(void){
	cout << "\nPressione ENTER para continuar..." << endl;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cin.get();
}

int showMenu(void){
	int op;
	
	cout << "\t\033[42;30m-----------------------------------------------------------------------\033[0m"<< endl;
	cout << "\t\033[42;30m|                                UFJF                                 |\033[0m" <<endl;
	cout << "\t\033[42;30m|                                                                     |\033[0m" << endl;
	cout << "\t\033[42;30m|\t\tTrabalho de Teoria dos Grafos V1.0       	      \t|\033[0m" << endl;
	cout << "\t\033[42;30m|                                                                     |\033[0m" << endl;	
	cout << "\t\033[42;30m|                                                                     |\033[0m" << endl;
	cout << "\t\033[42;30m|Por: Mateus C. Marim                                                 |\033[0m" << endl;
	cout << "\t\033[42;30m|                                                                     |\033[0m" << endl;
	cout << "\t\033[42;30m-----------------------------------------------------------------------\033[0m"<< endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Escolha uma opcao:\n" << endl;
	cout << "1 - Adicionar vertice" << endl;
	cout << "2 - Adicionar aresta" << endl;
	cout << "3 - Remover vertice" << endl;
	cout << "4 - Remover aresta" << endl;
	cout << "5 - Imprimir adjacentes ao vertice v" << endl;
	cout << "6 - Ordem do grafo" << endl;
	cout << "7 - Tamanho do grafo" << endl;
	cout << "8 - Grau maximo do grafo" << endl;
	cout << "9 - Grau do vertice v" << endl;
	cout << "10 - Grafo eh completo?" << endl;
	cout << "11 - Grafo eh regular?" << endl;
	cout << "12 - Grafo eh bipartido?" << endl;
	cout << "13 - Grafo eh conexo?" << endl;
	cout << "14 - Vertice v eh adjacente a u?" << endl;
	cout << "15 - Imprimir lista de adjacencias." << endl;
	cout << "16 - Sair..." << endl;
	cout << endl;
	cout << "> ";
	
	cin >> op;
		
	return op;
}

void executeOption(int op, Graph *grafo){
	switch(op){
	case 1:{
		int v;
		
		cout << "\nId do vertice que deseja adicionar: ";
		cin >> v;
		
		grafo->addVertex(v);
		waitUserAction();
		break;	
		}
	case 2:
		int n, ini, fim;
		cout << "\nQuantas arestas deseja adicionar? " << endl;
		cout << "> ";
		cin >> n;
		
		for(int i = 0; i < n; i++){ 
			cin >> ini >> fim;
			grafo->addEdge(ini, fim, 0);
		}
		
		waitUserAction();
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:{
		int v;
		cout << "\nDeseja imprimir os adjacentes de que vertice?" << endl;
		cout << "> ";
		cin >> v;
		vector<Edge*> adj = grafo->getAdjacents(v);
		vector<Edge*>::iterator itr;
		
		cout << endl;
		for(itr = adj.begin(); itr != adj.end(); itr++){
			cout << (*itr)->id << " ";
		}			
		cout << endl;
		
		waitUserAction();
		break;
		}
	case 6:
		cout << "\n" << grafo->getOrder() << endl; 
		waitUserAction();
		break;
	case 7:
		cout << "\n" << grafo->size() << endl; 
		waitUserAction();
		break;
	case 8:
		
		break;
	case 9:
		
		break;
	case 10:
		if(grafo->isComplete()) cout << "\nO grafo eh completo." << endl; else cout << "\nO grafo nao eh completo." << endl;
		waitUserAction();
		break;
	case 11:{
		int k = grafo->isRegular();
	
		if(k >= 0){
			cout << "\nO grafo eh " << k << " regular." << endl;
		}else cout << "\nO grafo nao eh regular." << endl;
		
		waitUserAction();
		break;
		}
	case 12:
		if(grafo->isBipartite()){
			cout << "\nO grafo eh bipartido." << endl;
		}else cout << "\nO grafo nao eh bipartido." << endl;
		
		waitUserAction();
		break;
	case 13:
		cout << (grafo->isConnected()?"\nEh conexo.":"\nNao eh conexo.") << endl;
		waitUserAction();
		break;
	case 14:
		int u, v;
		
		cout << "\nVertice u: ";
		cin >> u;
		cout << "\nVertice v: ";
		cin >> v;
		
		cout << endl;
		if(grafo->isAdjacent(u,v)){
			cout << u << " eh adjacente a " << v << "." << endl;
		}else cout << u << " nao eh adjacente a " << v << "." << endl;
		
		waitUserAction();
		break;
	case 15:
		grafo->print();
		waitUserAction();
		break;
	case 16:
		sair = true;
		break;
	}
}
