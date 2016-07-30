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

		string a(argv[2]), s(argv[3]);
		int seed = stoi(s), bseed;
		Solution *bS = new Solution;
		bS->funcVal = INF;

		for(int i = 0; i < 500; i++){
			seed += 10;
			Solution *S = problem.constructGreedyRandomizedSolution(stod(a), seed);
			if(S->funcVal < bS->funcVal){
				bS = S;
				bseed = seed;
			}
		}
		
		cout << bS->funcVal << "," << bS->nVehi << "," << stod(a) << "," << bseed;
	}
}
