#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	cout << "Is the graph oriented? (y/n) ";
	char res;
	cin >> res;
	
	Graph *grafo = new Graph(5, (res == 'y'));
	int u,v;	
	string out = (res == 'y')?"yes":"no";
	
	cout << out << endl;
	
	while(cin >> u >> v){
		grafo->addEdge(u, v);
	}
	//cin >> u >> v;
	
	cout << "Add Vertex 6" << endl;
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
	grafo->print();
	delete grafo;
}
