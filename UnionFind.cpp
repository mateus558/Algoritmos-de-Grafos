#include "UnionFind.h"

Union_Find::Union_Find(int n){
	for (int i = 0; i < n; ++i){
		id[i] = i;
		sz[i] = 1;
	}
}

int Union_Find::root(int i){
	while(i != id[i]){
		id[i] = id[id[i]];	//path Compression
		i = id[i];
	}
	return i;
}

int Union_Find::find(int p, int q){
	return root(p)==root(q);
}

void Union_Find::unite(int p, int q){
	int i = root(p);
	int j = root(q);

	if(sz[i] < sz[j]){
		id[i] = j;
		sz[j] += sz[i];
	}else{
		id[j] = i;
		sz[i] += sz[j];
	}
}
