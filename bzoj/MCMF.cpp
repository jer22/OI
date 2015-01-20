#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 1000
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int x)
		: from(u), to(v), cap(c), flow(f), cost(x) {}
};

int V, E;
vector<int> G[MAXV];
vector<Edge> edges;
bool done[MAXV];
int dist[MAXV];
int previous[MAXV];	// previous[i]表示顶点i的前一条弧在edges的索引
int a[MAXV];	// a[i]表示当前顶点i的可改进流量

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

bool spfa(int s, int t, int& flow, int& cost) {
	for (int i = 0; i <= V; i++) {
		dist[i] = INF;
	}
	dist[s] = 0;
	memset(done, 0, sizeof(done));
	done[s] = 1;
	previous[s] = 0;
	a[s] = INF;
	queue<int> buff;
	buff.push(s);
	while(!buff.empty()) {
		int current = buff.front();
		buff.pop();
		done[current] = 0;
		for (int i = 0; i < G[current].size(); i++) {
			Edge& e = edges[G[current][i]];
			if (e.cap > e.flow && dist[e.to] > dist[current] + e.cost) {
				dist[e.to] = dist[current] + e.cost;
				previous[e.to] = G[current][i];
				a[e.to] = min(a[current], e.cap - e.flow);
				if (!done[e.to]) {
					done[e.to] = 1;
					buff.push(e.to);
				}
			}
		}
	}
	if (dist[t] == INF)
		return false;
	flow += a[t];
	cost += dist[t] * a[t];
	for (int u = t; u != s; u = edges[previous[u]].from) {
		edges[previous[u]].flow += a[t];
		edges[previous[u] ^ 1].flow -= a[t];
	}
	return true;
}

int minCostMaxFlow(int s, int t) {
	int flow = 0;
	int cost = 0;
	while(spfa(s, t, flow, cost));
	return cost;
}

int main( void ) {
	scanf("%d %d", &V, &E);
	int e = E;
	int u, v, c, cost;
	for (int i = 0; i < e; i++) {
		scanf("%d %d %d %d", &u, &v, &c, &cost);
		addEdge(u, v, c, cost);
	}
	printf("%d\n", minCostMaxFlow(1, V));
	return 0;
}
