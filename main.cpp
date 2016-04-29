#include "Graph.h"
#include <limits>


using namespace std;

bool sair = false;

void clear(void);
int showMenu(void);
void executeOption(int);
void waitUserAction(void);

int main(int argc, char** argv){
	if(argc == 3){
		string input(argv[1]), output(argv[2]);
		clear();
		while(true){	
			if(sair){
				return 0;
			}
		
			int option = showMenu();
			
			executeOption(option);
			
			clear();
		}
		
	}else{
		cerr << "Run the program in the following format:" << endl;
		cerr << "./T1_201465559AC <input filename> <output filename>" << endl; 
	}
	
	return 0;
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

void executeOption(int op){
	switch(op){
	case 1:
		
		break;	
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		
		break;
	case 6:
		
		break;
	case 7:
		
		break;
	case 8:
		
		break;
	case 9:
		
		break;
	case 10:
		
		break;
	case 11:
		
		break;
	case 12:
		
		break;
	case 13:
		
		break;
	case 14:
		
		break;
	case 15:
		waitUserAction();
		break;
	case 16:
		sair = true;
		break;
	}
}
