#ifndef CVRP_H_INCLUDED
#define CVRP_H_INCLUDED
#define M_PI 3.14159265358979323846
#define INF 1000000000
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <list>
#include <sstream>
#include <vector>
#include <random>
//Capacited Vehicle Routing Problem with Time Window

using namespace std;

struct Point{
	int x, y;
	
	Point(): x(0), y(0) {}
	
	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

struct Costumer{
	Point *coord;
	double cost, ratio;
	int id;
	double saving;
	int demand;
	int rTime, dTime;
	double arrTime;
	int servTime;
	
	Costumer():	id(0),	demand(0),	rTime(0),	dTime(0),	coord(new Point),	servTime(0),	arrTime(0) {}
	Costumer(int id, Point* coord, int demand, int rtime, int dtime, int stime){
		this->id = id;
		this->demand = demand;
		this->coord = coord;
		this->servTime = stime;
		this->rTime = rtime;
		this->dTime = dtime;
	}
};

struct Route{
	vector<Costumer*> clients;
	int total_demand;
	int nVehi;
	double cost;
	
	Route(): cost(0.0), total_demand(0) {}
	
	void add_client(Costumer* c){
		clients.push_back(c);
	}
	
	int idleTime(){
		return clients[clients.size()-1]->dTime + clients[clients.size()-1]->servTime;
	}
	
	void compute_total_cost(){
		cost = 0.0;
		for(int c = 1; c < clients.size(); c++){
			double t = sqrt(pow(clients[c]->coord->x - clients[c-1]->coord->x,2) + pow(clients[c]->coord->y - clients[c-1]->coord->y,2));
			cost += t;
		}
	}
	
	void print(){
		double cost = 0.0;
		for(Costumer* c: clients){
			cout << c->id << " " << c->rTime << " " << c->dTime << endl;	
		}
	}
};

struct Solution{
	int nVehi;
	int funcVal;
	int best_result;
	double alpha;
	vector<Route*> sol;
};

struct parallel_cand{
	vector<Costumer*> cand;
};

struct Deposit{
	Point *coord;
	int id;
	int nVehicles;
	int cap;
	Deposit():	coord(new Point),	id(0),	nVehicles(0),	cap(0) {}
};	

class CVRP{
  private:
	Deposit dep;
	vector<Costumer*> clients;
	vector<bool> visited;
	vector<Route*> sol;
	double calculate_cost(Point *org, Point *dest);
	int compute_function_value(vector<Route*> S);
	void choose_alpha(vector<double> P, int rand, int &i);	
  public:
  	CVRP();
  	Solution* GRA(int max_iter, int block_iter, double granularity, double gama, int seed);
  	vector<vector<Costumer*> > update_list(vector<Route*> &solution, vector<double> &times, int &n);
  	void select_candidate(vector<Route*> &, vector<vector<Costumer*> > &, vector<double> &, vector<int> &, int &, vector<int> randPos, double alpha, int seed, mt19937 generator);
  	Solution* constructGreedyRandomizedSolution(double alpha, int seed);
  	void shrink_routes(vector<Route*> &solution);
  	void load_solomon_instance(string path);
  	void load_cordeau_instance(string path);
  	int deduce_nVehicles(int gama);
  	double angle_b2p(Point* a, Point* b);
  	void init_solution(vector<Route*> &, vector<double> &, vector<int> &, int &, vector<int>);
  	void save();
  	void print();
	~CVRP();
};

#endif
