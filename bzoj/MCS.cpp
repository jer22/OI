#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define MAXV 2000

using namespace std;

struct Edge {
	int to;
};

int V, E;
int peo[MAXV];
int label[MAXV];
int Q[MAXV];
vector<Edge> e[MAXV];

void MCS() {
	label[0] = -1;
	for (int i = V; i > 0; i--) {
		int max = 0;
		for (int j = 1; j <= V; j++) {
			if (!peo[j] && label[j] > label[max]) {
				max = j;
			}
		}
		peo[max] = i;
		Q[i] = max;
		for (int j = 0; j < (int)e[max].size(); j++) {
			if (!peo[e[max][j].to]) {
				label[e[max][j].to]++;
			}
		}
	}
}

int main( void ) {
	cin >> V >> E;
	int x, y;
	Edge temp;
	for (int i = 1; i <= E; i++) {
		scanf("%d %d", &x, &y);
		temp.to = x;
		e[y].push_back(temp);
		temp.to = y;
		e[x].push_back(temp);
	}
	MCS();
	return 0;
}
