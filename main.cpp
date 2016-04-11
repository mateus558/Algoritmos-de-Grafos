#include <iostream>
#include "Graph.h"

using namespace std;

int main(){
	Graph grafo(5);
	int u,v;	
	
	while(cin >> u >> v){
		grafo.addEdge(u, v);
	}
	//grafo.addVertex(6);
	grafo.print();
}
