/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Graph.h"
#include <limits>
#include <fstream>

using namespace std;

bool sair = false;

void clear(void);
int showMenu(void);
void executeOption(int, Graph*, string);
void waitUserAction(void);
void saveToFile(string, string);
Graph* populateWeightedGraph(string);	

int main(int argc, char** argv){
	if(argc == 3){
		string input(argv[1]), output(argv[2]);
		
		Graph *grafo = populateWeightedGraph(input);

		clear();
		cout << grafo->MSTPrim() << endl;
		while(true){	

			if(sair){
				return 0;
			}

			int option = showMenu();
			
			executeOption(option, grafo, output);
			
			clear();
		}
		
	}else{
		cerr << "Run the program in the following format:" << endl;
		cerr << "./T1_201465559AC <input filename> <output filename>" << endl; 
	}
	
	return 0;
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

	Graph *grafo = new Graph(nV, Graph::ehOriented(edges));

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
	cout << "\t\033[42;30m|\t\tTrabalho de Teoria dos Grafos V1.5       	      \t|\033[0m" << endl;
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
	cout << "16 - Criar grafo induzido." << endl;
	cout << "17 - Grafo complementar." << endl;
	cout << "18 - Numero de componentes conectados." << endl;
	cout << "19 - Eh vertice de articulacao?" << endl;
	cout << "20 - Eh aresta ponte." << endl;
	cout << "21 - Sair..." << endl;
	cout << endl;
	cout << "> ";
	
	cin >> op;
		
	return op;
}

void saveToFile(string fileName, string output){
	char res;
	cout << "\nDeseja salvar a saida?(y/n)" << endl;
	cin >> res;
	if(res == 'y'){
		ofstream out(fileName, ios::app);
	
		if(!out){
			cout << "Arquivo de saida nao pode ser aberto." << endl;
		}	
	
		out << output;
	
		out.close();
	}
}

void executeOption(int op, Graph *grafo, string output){
	switch(op){
	case 1:{
		int v;
		ostringstream stream;
		
		cout << "\nId do vertice que deseja adicionar: ";
		cin >> v;
		
		grafo->addVertex(v);
		stream << "\nVertice " << v << " adicionado.\n"; 
		
		saveToFile(output, stream.str());
		waitUserAction();
		break;	
		}
	case 2:{
		int n, ini, fim;
		ostringstream stream;
		
		cout << "\nQuantas arestas deseja adicionar? " << endl;
		cout << "> ";
		cin >> n;
		
		for(int i = 0; i < n; i++){ 
			cout << "Id do vertice de origem " << i << ": ";
			cin >> ini;
			cout << "Id do vertice de chegada " << i << ": ";
			cin >> fim;
			grafo->addEdge(ini, fim, 0);
			stream << "\nAresta " << ini << "->" << fim << " adicionada ao grafo.\n";
		}
		saveToFile(output, stream.str());
		waitUserAction();
		break;
		}
	case 3:{
		int n, v;
		cout << "\nQuantos vertices deseja remover? " << endl;
		cout << "> ";
		cin >> n;
		ostringstream stream;
		
		for(int i = 0; i < n; i++){
			cout << "Id do vertice " << i << ": ";  
			cin >> v;
			grafo->removeVertex(v);
			stream << "\n"<< v << " foi removido.\n";
			cout << stream.str();
		}
		
		saveToFile(output, stream.str());
		waitUserAction();
		break;
		}
	case 4:{
		int v, u;
		ostringstream stream;
		
		cout << "\nQual aresta deseja remover?"<< endl;
		cout << "Id do vertice de origem: ";
		cin >> v;
		cout << "Id do vertice de chegada: ";
		cin >> u;
		
		grafo->deleteEdge(v, u);
		stream << "\nAresta " << v << "->" << u << " removida.\n"; 
		
		saveToFile(output, stream.str());
		waitUserAction();
		break;
		}
	case 5:{
		int v;
		cout << "\nDeseja imprimir os adjacentes de que vertice?" << endl;
		cout << "> ";
		cin >> v;
		
		ostringstream stream;
		vector<Edge*> adj = grafo->getAdjacents(v);
		vector<Edge*>::iterator itr;
		
		if(adj.size() > 0){
			stream << endl;
			stream << "Adjacentes do vertice " << v << ": ";
			for(itr = adj.begin(); itr != adj.end(); itr++){
				stream << (*itr)->id << " ";
			}			
			stream << endl;
		}else stream << "Vertice nao existe!\n" << endl;
		
		string out = stream.str();
		
		cout << out;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		}
	case 6:{
		int o = grafo->getOrder();
		stringstream ss;
		ss << o;
		string str = ss.str();
		
		cout << "\n" << str << endl; 
			
		str = str + '\n';
		saveToFile(output, str);
		waitUserAction();
		break;
		}
	case 7:{
		int o = grafo->size();
		stringstream ss;
		ss << o;
		string str = ss.str();
		
		cout << "\n" << str << endl; 
			
		str = str + '\n';
		saveToFile(output, str);
		waitUserAction();
		break;
		}
	case 8:{
		ostringstream stream;
		
		cout << endl;
		stream << grafo->getMaxGraphDegree() << '\n';
		cout << stream.str();
		
		saveToFile(output, stream.str());
		waitUserAction();
		break;
		}
	case 9:{
		int v;
		ostringstream stream;
		
		cout << "\nDeseja saber o grau de qual vertice? " << endl;
		cout << "> ";
		cin >> v;
		int g = grafo->getVertexDegree(v);
		if(g != -1){
			stream << "O vertice " << v << " tem grau " << g << "\n";
		}else cout << "Vertice nao existe" << endl;
		string out(stream.str());
		cout << out;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		}
	case 10:{
		string outp = (grafo->isComplete())?"\nO grafo eh completo.\n":"\nO grafo nao eh completo.\n";
		
		cout << outp;
		
		saveToFile(output, outp);
		waitUserAction();
		break;
		}
	case 11:{
		int k = grafo->isRegular();
		stringstream ss;
		ss << k;
		string str = ss.str();
		
		string outp = (k >= 0)?"\nO grafo eh " + str + " regular.\n":"\nO grafo nao eh regular.\n";
		
		cout << outp << endl;
		
		saveToFile(output, outp);		
		waitUserAction();
		break;
		}
	case 12:{
		string outp = (grafo->isBipartite())?"\nO grafo eh bipartido.\n":"\nO grafo nao eh bipartido.\n";
		
		cout << outp;
		
		saveToFile(output, outp);		
		waitUserAction();
		break;
		}
	case 13:{
		string outp = (grafo->isConnected())?"\nEh conexo.\n":"\nNao eh conexo.\n";

		cout << outp;
	
		saveToFile(output, outp);				
		waitUserAction();
		break;
		}
	case 14:{
		int u, v;
		
		cout << "\nVertice u: ";
		cin >> u;
		cout << "\nVertice v: ";
		cin >> v;
		
		cout << endl;
		
		stringstream ss;
		ss << u;
		string str = ss.str();
		stringstream ss1;
		ss1 << v;
		string str1 = ss1.str();
		
		string out = (grafo->isAdjacent(u,v))?str + " eh adjacente a " + str1 + ".\n":str + " nao eh adjacente a " + str1 + ".\n";
		cout << out; 
		
		saveToFile(output, out);				
		waitUserAction();
		break;
		}
	case 15:{
		string out = grafo->print();
		cout << out << endl;
		saveToFile(output, out);				
		waitUserAction();
		break;
		}
	case 16:{
		int n, u;
		vector<int> V;
		cout << "\nInforme a quantidade de vertices: ";
		cin >> n;
		for(int i = 0; i < n; i++){
			cout << "Entre com o vertice " << i << ": ";
			cin >> u;
			V.push_back(u);
		} 

		AdjacencyList *grap = Graph::inducedGraph(V, grafo);
		if(grap == NULL){
			cout << "Erro na entrada do usuário!"<< endl;
			return;
		}
		Vertex *itr = grap->head;
		ostringstream stream;
		
		cout << '\n' << endl;
		stream << '\n' << endl;
		while(itr != grap->tail->next){
			cout << itr->id << ": ";
			stream << itr->id << ": ";
			for(Edge* adj = itr->adjL; adj != NULL; adj = adj->next){
				cout << "(" <<adj->id << ", " << adj->weight << ")" << " -> ";
				stream << "(" <<adj->id << ", " << adj->weight << ")" << " -> ";
			}
			cout << endl;
			stream << '\n';
			
			itr = itr->next; 
		}
		
		saveToFile(output, stream.str());
		waitUserAction();
		break;
		}
	case 17:{
		Graph *compGrafo = grafo->complementaryGraph();
		
		string out = compGrafo->print();
		char k;
		
		cout << "\nDeseja imprimir a lista de adjacencias na tela? (y/n)\n";
		cout << "> ";
		cin >> k;
		
		if(k == 'y') cout << out << endl;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		}
	case 18:{
		ostringstream stream;
		string out;
		
		stream << "\nExistem " << grafo->nConnectedComponents() << " Componentes conectados.\n";
		out = stream.str();
		cout << out;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		}
	case 19:{
		int v;
		ostringstream stream;
		string out;
		
		cout << "\nInforme o vertice para verificar se eh de articulacao: ";
		cin >> v;
		
		if(grafo->isArticulation(v)){
			stream << "\nO vertice " << v << " eh de articulacao.\n";
		}else{
			stream << "\nO vertice " << v << " nao eh de articulacao.\n";
		}
		
		out = stream.str();
		cout << out;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		} 
	case 20:{
		int u, v;
		ostringstream stream;
		string out;
		
		cout << "\nEntre com a aresta para ser testada.\n";
		cout << "Aresta de origem: ";
		cin >> u;
		cout << "Aresta de destino: ";
		cin >> v;
		
		if(grafo->isBridge(u, v)){
			stream << "\nA aresta (" << u << ", " << v << ") eh uma ponte.\n";
		}else{
			stream << "\nA aresta (" << u << ", " << v << ") nao eh uma ponte.\n";
		}
		
		out = stream.str();
		cout << out;
		
		saveToFile(output, out);
		waitUserAction();
		break;
		}
	case 21:
		delete grafo;
		sair = true;
		break;
	}
}
