#ifndef UNION_FIND_H_
#define UNION_FIND_H_
#define MAX 10010

class Union_Find{
  private:
	int id[MAX], sz[MAX];  

  public:
	Union_Find(int n);
	int root(int i);
	int find(int p, int q);
	void unite(int p, int q);
};

#endif
