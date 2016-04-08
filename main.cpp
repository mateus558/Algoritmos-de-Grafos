#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	Graph grafo(5);
	int u,v;	
	
	cin >> u >> v;
	grafo.addEdge(u,v);
	
	cin >> u >> v;
	grafo.addEdge(u,v);
	cin >> u >> v;
	grafo.addEdge(u,v);
	cin >> u >> v;
	grafo.addEdge(u,v);
	
	cout << "deu" << endl;
}
