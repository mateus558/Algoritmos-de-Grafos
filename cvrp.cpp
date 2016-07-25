#include "cvrp.h"

bool saving_heuristic(Costumer* a, Costumer* b){	
    return a->saving > b->saving;
}

bool cost_heuristic(Costumer *a, Costumer *b){	
    return a->cost < b->cost;
}

CVRP::CVRP(){};

void CVRP::load_solomon_instance(string path){
	ifstream input(path);
	int id, x, y, demand, rtime, dtime, stime;
	
	if(!input){
		cerr << "File could not be opened." << endl;
		return;
	}
	
	input >> dep.nVehicles >> dep.cap;
	input >> id >> dep.coord->x >> dep.coord->y >> demand >> rtime >> dtime >> stime;
	
	while(input >> id >> x >> y >> demand >> rtime >> dtime >> stime){
		Point *temp = new Point(x, y);
		Costumer *c = new Costumer(id, temp, demand, rtime, dtime, stime);
		clients.push_back(c);
	}
	
	visited = vector<bool>(clients.size(),false);
}

void CVRP::load_cordeau_instance(string path){
	ifstream input(path);
	int id, x, y, demand, rtime, dtime, stime;
	
	if(!input){
		cerr << "File could not be opened." << endl;
		return;
	}
	
	input >> dep.nVehicles >> dep.cap;
	input >> id >> dep.coord->x >> dep.coord->y >> stime >> demand >> rtime >> dtime;
	string str;
	while(getline(input, str)){
		vector<string> elems;
    	stringstream ss(str);
    	string item;
    
    	while(getline(ss, item, ' ')){
	        elems.push_back(item);
	    }
	    Point *temp = new Point(stoi(elems[1]), stoi(elems[2]));
		Costumer *c = new Costumer(stoi(elems[0]) , temp, stoi(elems[4]), stoi(elems[5]), stoi(elems[6]), stoi(elems[3]));
		clients.push_back(c);
	}
	
	visited = vector<bool>(clients.size(),false);
}

double CVRP::calculate_cost(Point *org, Point *dest){
	return sqrt(pow(dest->x - org->x,2) + pow(dest->y - org->y,2));
}
//Deduction for the number of vehicles
int CVRP::deduce_nVehicles(int gama){
	int sum = 0;
	
	for(Costumer* c : clients){
		sum += c->demand;
	}

	return (int)(sum/dep.cap) + gama;
}
//angle of 2 points from dot product 0-360 degrees
double CVRP::angle_b2p(Point* a, Point* b){
	int dprod = (a->x * b->x) + (a->y * b->y);
	double anorm = sqrt(a->x*a->x + a->y*a->y);
	double bnorm = sqrt(b->x*b->x + b->y*b->y);
	
	return acos(dprod/(anorm*bnorm))*360;	
}

vector<vector<Costumer*> > CVRP::update_list(vector<Route*> &solution, vector<double> &times, int &n){
	vector<Costumer*>::iterator itr = clients.begin();
	vector<vector<Costumer*> > candidates(solution.size(), vector<Costumer*> ());
	
	for(; itr != clients.end(); itr++){
		Costumer* co = *(itr);
		
		for(int r = 0; r < solution.size(); r++){
			if(!solution[r]->clients.empty()){
				int c = solution[r]->clients.size()-1;
				Costumer* org = solution[r]->clients[c];
				int cost = calculate_cost(org->coord, co->coord);
				//Time arrival to verify if the vehicle can get to the client before the due time
				double arrivalTime = times[r] + cost;
				//Verify if the client wasn't visited and if the vehicle is on time
				if(!visited[co->id - 1] && co->id != org->id && co->dTime >= arrivalTime){
					Point *i = solution[r]->clients[c]->coord;
					Point *j = co->coord;
					co->saving = calculate_cost(j, dep.coord) + calculate_cost(dep.coord, i) - calculate_cost(i, j) + co->dTime - co->rTime;
					co->cost = cost;
					co->arrTime = arrivalTime;
					candidates[r].push_back(co); 
				}
			}
		}
	}

	for(int i = 0; i < candidates.size(); i++){
		if(candidates[i].size() != 0){
			return candidates;	
		}	
	}
	
	candidates.push_back(vector<Costumer*> ());
	int k = candidates.size() - 1;

	for(int i = 0; i < clients.size(); i++){
		Costumer *cos = clients[i];
		if(!visited[cos->id - 1]){
			int cost = calculate_cost(dep.coord, cos->coord);
		
			if(candidates[k].empty()){
				candidates[k].push_back(cos);
			}else if(candidates[k][0]->cost > cost){
				candidates[k][0] = cos;
			}
		}
	}	
	if(candidates[k].size() > 0){
		visited.push_back(false);
		visited[candidates[k][0]->id - 1] = true;	
		times.push_back(0.0);
		times[k] += candidates[k][0]->cost + candidates[k][0]->servTime;
		candidates[k][0]->arrTime = candidates[k][0]->cost;
		n++;
		solution.push_back(new Route);
		solution[solution.size()-1]->clients.push_back(candidates[k][0]);
	 }
	return candidates;
}

void CVRP::select_candidate(vector<Route*> &solution, vector<vector<Costumer*> > &candidates, vector<double> &times, vector<int> &route_capacity, int &n, vector<int> randPos, double alpha, int seed, mt19937 generator){
	
	randPos = vector<int>(solution.size(), 0);
	for(int i = 0; i < solution.size(); i++){	
		if(!candidates[i].empty()){
			uniform_int_distribution<int> dis(1, candidates[i].size());
			int pos = ((dis(generator)-1)*alpha);
			randPos[i] = pos;
		}
	}

	for(int r = 0; r < candidates.size(); r++){
		if(!solution[r]->clients.empty() && !candidates[r].empty()){
			Costumer* cand = candidates[r][randPos[r]];
			if(!visited[cand->id - 1]){
				//Update time
				double waitTime = 0.0;
		
				if(cand->rTime > cand->arrTime){
					waitTime = cand->rTime - cand->arrTime; 	
				}
				//Time = arrivalTime + serviceTime + waitTime
				times[r] = cand->arrTime + cand->servTime + waitTime;
				//Add the client to the solution and set as visited
				solution[r]->clients.push_back(cand);
				visited[cand->id - 1] = true;
				n++;
			}
		}
	}
}

//Select initial clients from each 360/nV angle
void CVRP::init_solution(vector<Route*> &solution, vector<double> &time, vector<int> &route_capacity, int &n, vector<int> randPos){
	double angle = 360/dep.nVehicles;
	
	for(int i = 0; i < clients.size(); i++){
		//Angle between the deposit and the i-th client
		double ang_b2p = angle_b2p(dep.coord, clients[i]->coord);
		//Calculate pos of Ci
		double posd = ang_b2p/angle;
		int pos = ceil(posd);
		
		int cost = calculate_cost(dep.coord, clients[i]->coord);
		
		clients[i]->cost = cost;
				
		if(solution[pos]->clients.size() == 0){
			solution[pos]->clients.push_back(clients[i]);
			route_capacity[pos] = clients[i]->demand;
			time[pos] = clients[i]->cost;
		}else if(cost < solution[pos]->clients[0]->cost){	//if the client i is better than the i - 1 for that route
			solution[pos]->clients[0] = clients[i];
			route_capacity[pos] = clients[i]->demand;
			time[pos] = clients[i]->cost;
		}
	}
	
	for(int r = 0; r < solution.size(); r++){
		if(!solution[r]->clients.empty()){
			visited[solution[r]->clients[0]->id - 1] = true;	
			time[r] += solution[r]->clients[0]->cost + solution[r]->clients[0]->servTime;
			solution[r]->clients[0]->arrTime = solution[r]->clients[0]->cost;
			n++;
		}
	}
}

Solution* CVRP::constructGreedyRandomizedSolution(double alpha, int seed){
	mt19937 generator(seed);
	int n = 0;
	double waitTime = 0.0;
	visited = vector<bool>(clients.size(), false);
	int nVehi = deduce_nVehicles(0);
	vector<Route*> solution(nVehi, new Route);
	vector<int> randPos(0, clients.size());
	vector<int> route_capacity(nVehi, 0);
	vector<double> routes_times(nVehi, 0.0);
	vector<vector<Costumer*> > sol_candidates(solution.size(), vector<Costumer*> ());
	
	dep.nVehicles = nVehi;
		
	for(int i = 0; i < solution.size(); i++){
		solution[i] = new Route;
		uniform_int_distribution<int> dis(0, clients.size()-1);
		randPos.push_back(dis(generator)*alpha);
	}
	
	//Initialize the solution with nearby close clients
	init_solution(solution, routes_times, route_capacity, n, randPos);
	
	while(n != clients.size()){
		//Update the list of candidates
		sol_candidates = update_list(solution, routes_times, n);
		
		for(int c = 0; c < sol_candidates.size(); c++){
			sort(sol_candidates[c].begin(), sol_candidates[c].end(), cost_heuristic);
		}
		//shrink_routes(solution);
		select_candidate(solution, sol_candidates, routes_times, route_capacity, n, randPos, alpha, seed, generator);
	}
	double sum = 0.0;	
	for(Route *r : solution){
		for(Costumer *c : r->clients){
			sum += c->cost;
		}
		sum += calculate_cost(dep.coord, r->clients[r->clients.size()-1]->coord);
	}
	
	Solution *sol = new Solution;
	sol->funcVal = sum;
	sol->nVehi = solution.size();
	sol->sol = solution;
	/*for(int i = 0; i < solution.size(); i++){
		solution[i]->clients.push_back(new Costumer(0, dep.coord,0,0,0,0));
	}
	sol = solution;
	for(Route *r : solution){
		for(int i = 0; i < r->clients.size()-1; i++){
			cout << r->clients[i]->id << ":" << r->clients[i]->arrTime + r->clients[i]->servTime << " " << r->clients[i+1]->id << ":" << r->clients[i+1]->dTime << endl;  
		}
		cout << endl;
	}
	save();*/
	return sol;
}

int CVRP::compute_function_value(vector<Route*> S){
	int sum = 0;
	
	for(Route* r : S){
		for(Costumer* c : r->clients){
			sum += c->cost;
		}
	}
	
	return sum;
}

void CVRP::choose_alpha(vector<double> P, int rand, int &i){
	vector<double> prod(P.size(), 0.0);
	double sum;
	
	sum = 0.0;
	
	for(i = 0; i < P.size(); i++){
		prod[i] = P[i]*1000;
	}

	for(i = 0; sum < rand && i < prod.size(); i++){
		sum += prod[i];
	}
}

/*------------------ Reactive Greedy Algorithm ------------------
	A - Vector of alphas
	P - Vector of probabilities
	Q - Medians of the best value divided by the number of times that the alphas were used
	S - Greedy randomized constructive solution
	
	Implemented using the mersenne twister random generator for better results
*/

Solution* CVRP::GRA(int max_iter, int block_iter, double granularity, double gama, int seed){
	mt19937 generator(seed);
	uniform_int_distribution<int> dis(0, 1000);
	vector<double> A, P, Q;
	vector<int> n_alpha, alpha_results;
	Solution* S;
	int best_value = INF, S_value;	//Set the best value to infinity
	double sum, alpha;
	int i, itr, a, rand;

	for(double i = 0.0; i < 0.5; i += granularity, A.push_back(i)); //Initialize alphas, according with the granularity
	
	alpha_results = vector<int>(A.size(), 0);
	n_alpha = vector<int>(A.size(), 0);
	Q = vector<double>(A.size(), 0.0);
	
	for(i = 0; i < A.size(); i++, P.push_back((double)(1.0/A.size()))); //Initialize probabilities with uniform distribution	
	for(itr = 0; itr < max_iter; itr++){
		rand = dis(generator);
		choose_alpha(P, rand, a);//Randomly choose an alpha
		alpha = A[a];
		n_alpha[a]++;
		
		S = constructGreedyRandomizedSolution(alpha, seed);
		
		S_value = S->funcVal;
		alpha_results[a] += S_value;
		best_value = (S_value < best_value)?S_value:best_value;	//Update the best result
		
		if(itr%block_iter == 0){ //Update vector of probabilities
			sum = 0.0;

			for(i = 0; i < P.size(); i++){
				Q[i] = (double)(pow((n_alpha[i] != 0)?alpha_results[i]/n_alpha[i]:(1.0/A.size()), gama));
				sum += Q[i];
			}
			
			for(i = 0; i < P.size(); i++){
				P[i] = Q[i]/sum;
			}
		}
	}
	int m = 0, ind;
	for(int i = 0; i < P.size(); i++){
		m = (P[i] > P[m])?P[i], ind = i:m;
	}
	
	S->best_result = best_value; 
	S->alpha = A[ind];
	
	return S;
}

void CVRP::save(){
	string str;
	string n = "CVRPwTW";
	string ext = ".dat";
	
	for(int r = 0; r < sol.size(); r++){
		
		if(r > 9){
			char nm = '0' + 1;
			int k = r - 10;
			char nm1 = '0' + k;
			str = n + nm + nm1 + ext;
		}else{
			char nm = '0' + r;
			str = n + nm + ext;
		}

		ofstream out(str);
		out << dep.coord->x << '\t' << dep.coord->y << endl;
		for(int c = 0; c < sol[r]->clients.size(); c++){
			out << sol[r]->clients[c]->coord->x << '\t' << sol[r]->clients[c]->coord->y << endl; 
			
		}
		out << dep.coord->x << '\t' << dep.coord->y << endl;
		out.clear();
		
	}
}

void CVRP::print(){
	cout << "Deposit:" << endl;
	cout << dep.id << " " << dep.coord->x << " " << dep.coord->y << " " << dep.nVehicles << " " << dep.cap << endl;
	cout << endl;
	cout << "Clients:" << endl;
	vector<Costumer*>::iterator itr = clients.begin();
	for(;itr != clients.end(); itr++){
		cout << (*(itr))->id << " " << (*(itr))->coord->x << " " << (*(itr))->coord->y << " " << (*(itr))->rTime << " " << (*(itr))->dTime << " " << (*(itr))->demand << " " << (*(itr))->servTime << endl;
	} 
}

CVRP::~CVRP(){};
