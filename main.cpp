#include <iostream>
#include <ctime>
#include "Graph.h"

using namespace std;

int main(){
	int n, ini, fim, p;
	cin >> n;
	clock_t begin = clock();
	Graph *grafo = new Graph(n, true);
	
	cout << grafo->getOrder() << endl;
	while(cin >> ini >> fim >> p){
		grafo->addEdge(ini, fim, p);
	}
	cout << "Vertex 100 degree: " << grafo->getVertexDegree(100) << endl; 
	cout << "Graph degree: " << grafo->getMaxGraphDegree() << endl;
	cout << "Graph order: " << grafo->getOrder() << "\n" << endl;
	if(grafo->isRegular()){
		cout << "É " << grafo->isRegular() << " regular" << endl;
	}
	clock_t end = clock();
 	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	
	/*cout << "Is the graph oriented? (y/n) ";
	char res;
	cin >> res;
	
	Graph *grafo = new Graph(5, (res == 'y'));
	int u,v;	
	string out = (res == 'y')?"yes":"no";
	
	cout << out << endl;
	
	while(cin >> u >> v){
		grafo->addEdge(u, v);
	}*/
	/*Graph *grafo = new Graph(1000,true);
	clock_t begin = clock();
	grafo->geraCompleto();
 	clock_t end = clock();
 	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;*/
	/*cout << "Add Vertex 6" << endl;
	grafo->addVertex(6);
	grafo->print();
	cout << "Add Vertex 10" << endl;
	grafo->addVertex(10);
	grafo->print();
	cout << "Add Vertex 7" << endl;
	grafo->addVertex(7);
	grafo->print();
	cout << "Add Edge 6 to 1" << endl;
	grafo->addEdge(6,1);
	grafo->print();
	cout << "Add Edge 6 to 3" << endl;
	grafo->addEdge(6,3);
	grafo->print();
	cout << "Add Edge 6 to 2" << endl;
	grafo->addEdge(6,2);
	grafo->print();
	cout << "Vertex 6 degree: " << grafo->getVertexDegree(6) << endl; 
	cout << "Graph degree: " << grafo->getMaxGraphDegree() << endl;
	cout << "Graph order: " << grafo->getOrder() << "\n" << endl;
	
	cout << "remove vertex 2" << endl;
	grafo->removeVertex(2);
	grafo->print();
	cout << "Remove edge 6 to 1" << endl;
	grafo->deleteEdge(6,1);
	grafo->print();
	cout << "Remove vertex 6" <<endl;
	grafo->removeVertex(6);
	grafo->print();
	cout << "Remove edge 3 to 4" << endl;
	grafo->deleteEdge(3,4);
	grafo->print();*/
	/*	cout << elapsed_secs << endl;
		cout << "Graph degree: " << grafo->getGraphDegree() << endl;
	if(grafo->isComplete()){
		cout << "é completo" <<endl;
	}else cout << "Não  completo" << endl;
	if(grafo->isRegular()){
		cout << "É " << grafo->isRegular() << " regular" << endl;
	}*/
	grafo->print();
	cout << elapsed_secs << endl;
	delete grafo;
}
