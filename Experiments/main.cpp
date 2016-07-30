#include "cvrp.h"
#include <random>

using namespace std;

int main(int argc, char *argv[]){
	
	
	if(argc == 1){
					
	}else{
		string path(argv[1]);
		double alpha;
		CVRP problem;
		
		problem.load_solomon_instance(path);


		Solution *S = problem.constructGreedyRandomizedSolution(0, 1);

		cout << S->funcVal << "," << S->nVehi << endl;
		
	}
}
