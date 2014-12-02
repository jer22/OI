#include <iostream>
#include <vector>
#include <cstdio>

#define MAXV 1000000
#define INF 0x7FFFFFFF

using namespace std;

struct Edge {
	int v;
	int to;
};

int V, E;
int dist[MAXV];
vector<Edge> e[MAXV];
int S[MAXV];

void dijkstra(const int st) {
	for (int i = 0; i < V; i++) {
		if (i == st) {
			dist[st] = 0;
			continue;
		}
		dist[i] = INF;
	}
	for (int i = 0; i < V; i++) {
		int temp = INF;
		int current;
		for (int j = 0; j < V; j++) {
			if (!S[j] && dist[j] < temp) {
				current = j;
				temp = dist[j];
			}
		}
		S[current] = 1;
		Edge* t;
		for (int j = 0; j < (int)e[current].size(); j++) {
			t = &e[current][j];
			if (dist[current] + t -> v < dist[t -> to]) {
				dist[t -> to] = dist[current] + t -> v;
			}
		}
	}
}

int main( void ) {
	scanf("%d %d", &V, &E);
	int x, y, l;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &l);
		Edge temp;
		temp.v = l;
		temp.to = y;
		e[x].push_back(temp);
	}
	dijkstra(0);
	printf("Node 0 to node %d : %d", V-1, dist[V-1]);
	return 0;
}
