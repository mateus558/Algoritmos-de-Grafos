#include "cvrp.h"

bool IsMarkedToDelete(const Route* o)
{
    return o->clients.size() == 0;
}

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
	
	input >> dep.maxVehi >> dep.cap;
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

double CVRP::compute_cost(Point *org, Point *dest){
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
				int cost = compute_cost(org->coord, co->coord);
				//Time arrival to verify if the vehicle can get to the client before the due time
				double arrivalTime = times[r] + cost;
				//Verify if the client wasn't visited and if the vehicle is on time
				if(!visited[co->id - 1] && co->id != org->id && co->dTime >= arrivalTime){
					Point *i = solution[r]->clients[c]->coord;
					Point *j = co->coord;
					co->saving = compute_cost(j, dep.coord) + compute_cost(dep.coord, i) - compute_cost(i, j) + co->dTime - co->rTime;
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
			int cost = compute_cost(dep.coord, cos->coord);
		
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

void CVRP::select_candidate(vector<Route*> &solution, vector<vector<Costumer*> > &candidates, vector<double> &times, vector<int> &route_capacity, int &n, vector<int> randPos, double alpha, mt19937 generator){
	
	randPos = vector<int>(solution.size(), 0);
	for(int i = 0; i < solution.size(); i++){	
		if(!candidates[i].empty()){
			uniform_int_distribution<int> dis(0, candidates[i].size()-1);
			int pos = ((dis(generator))*alpha);
			randPos[i] = pos;
		}
	}

	for(int r = 0; r < candidates.size(); r++){
		if(!solution[r]->clients.empty() && !candidates[r].empty()){
			Costumer* cand = candidates[r][randPos[r]];
			if(cand && !visited[cand->id - 1]){
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
	double angle = 360.0/dep.nVehicles;
	double waitTime = 0.0;
		
	for(int i = 0; i < clients.size(); i++){
		//Angle between the deposit and the i-th client
		double ang_b2p = angle_b2p(dep.coord, clients[i]->coord);
		//compute pos of Ci
		double posd = ang_b2p/angle;
		int pos = floor(posd);
		
		int cost = compute_cost(dep.coord, clients[i]->coord);
		
		clients[i]->cost = cost;
			
		if(clients[i]->cost < clients[i]->rTime){
			waitTime = clients[i]->rTime - clients[i]->cost;
		}
		
		clients[i]->waitTime = waitTime;
				
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
		if(!solution[r]-> clients.empty()){
			Costumer *c = solution[r]->clients[0];
			visited[solution[r]->clients[0]->id - 1] = true;
			time[r] += c->cost + c->servTime + c->waitTime;
			c->arrTime = c->cost + waitTime;
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
	dep.nVehicles = (nVehi > 0)?nVehi:1;
	vector<Route*> solution(dep.nVehicles, new Route);
	vector<int> randPos(0, clients.size());
	vector<int> route_capacity(dep.nVehicles, 0);
	vector<double> routes_times(dep.nVehicles, 0.0);
	vector<vector<Costumer*> > sol_candidates(solution.size(), vector<Costumer*> ());
	//Generate random positions
	uniform_int_distribution<int> dis(0, clients.size()-1);
	for(int i = 0; i < solution.size(); i++){
		solution[i] = new Route;
		randPos.push_back(dis(generator)*alpha);
	}
	
	//Initialize the solution with nearby close clients
	init_solution(solution, routes_times, route_capacity, n, randPos);
	
	while(n != clients.size()){
		//Update the list of candidates
		sol_candidates = update_list(solution, routes_times, n);
		
		for(int c = 0; c < sol_candidates.size(); c++){
			sort(sol_candidates[c].begin(), sol_candidates[c].end(), saving_heuristic);
		}

		select_candidate(solution, sol_candidates, routes_times, route_capacity, n, randPos, alpha, generator);
	}

	vector<Route*>::iterator itr = solution.begin();
	
	solution.erase(
    remove_if(solution.begin(), solution.end(), IsMarkedToDelete),
    solution.end());
    
	Solution *sol = new Solution;
	sol->nVehi = solution.size();
	sol->sol = solution;
	
	double t_cost = 0.0;
	Costumer *ant;
	
	for(Route *r : sol->sol){
		for(Costumer *c : r->clients){
			t_cost += compute_cost((t_cost == 0.0)?dep.coord:ant->coord, c->coord); 
			ant = c;
		}
		t_cost += compute_cost(ant->coord, dep.coord);	
	}
	
	//verify_solution(sol, c);

	sol->funcVal = t_cost;

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
	Solution *S, *bS = new Solution;
	double best_value = INF, S_value;	//Set the best value to infinity
	double sum, alpha;
	int i, itr, a, rand, nV;
	
	A.push_back(0.0);
	for(double i = 0.0; i < 0.9; i += granularity, A.push_back(i)); //Initialize alphas, according with the granularity
	
	bS->funcVal = INF;
	alpha_results = vector<int>(A.size(), 0);
	n_alpha = vector<int>(A.size(), 0);
	Q = vector<double>(A.size(), 0.0);
	
	for(i = 0; i < A.size(); i++, P.push_back((double)(1.0/A.size()))); //Initialize probabilities with uniform distribution	
	
	for(itr = 0; itr < max_iter; itr++){
		rand = dis(generator);
		choose_alpha(P, rand, a);//Randomly choose an alpha
		//cout << a << endl;
		alpha = A[a];
		n_alpha[a]++;
		
		S = constructGreedyRandomizedSolution(alpha, seed);
		
		S_value = S->funcVal;
		alpha_results[a] += S_value;

		if(S_value < bS->funcVal){
			bS = S;
			bS->alpha = alpha;
		}

		if(itr%block_iter == 0){ //Update vector of probabilities
			sum = 0.0;

			for(i = 0; i < P.size(); i++){
				Q[i] = (double)(pow((alpha_results[i] != 0)?bS->funcVal/alpha_results[i]:(1.0/A.size()), gama));
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
	
	return bS;
}

bool CVRP::verify_solution(Solution *S, double &res){
	vector<Route*> s = S->sol;
	double time = 0.0;
	int i = 0, cost = 0.0, total_cost = 0.0;
	Costumer *ant;
	
	for(Route *r : s){
		for(Costumer *c : r->clients){
			cost = (i == 0)?compute_cost(dep.coord, c->coord):compute_cost(ant->coord, c->coord);			
			if(time < c->rTime){ 
					time += c->rTime + c->servTime; 
			}else if(time >= c->rTime){
					time += cost + c->servTime;
			}else if(time > c->dTime){
					return false;
			}
			total_cost += cost;
			ant = c;
		}

		time += compute_cost(ant->coord, dep.coord);
		time = 0.0;
	}
	
	res = total_cost;

	return true;
}

/*void CVRP::save(){
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
}*/

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
