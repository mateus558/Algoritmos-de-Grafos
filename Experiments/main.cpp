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

		clock_t begin = clock();				
		Solution *S = problem.constructGreedyRandomizedSolution(0, 1);
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << S->funcVal << "," << S->nVehi << "," << elapsed_secs << endl;
		
	}
}
