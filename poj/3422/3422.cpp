#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f
#define S (n * n * 2 + 1)
#define T (n * n * 2 + 2)

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, k;
vector<int> G[5005];
vector<Edge> edges;

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

int pre[5005];
int a[5005];
int dist[5005];
int vis[5005];
bool spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[S] = 0;
	vis[S] = 1;
	pre[S] = -1;
	a[S] = INF;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge &e = edges[G[current][i]];
			if (e.cap > e.flow && dist[e.to] > dist[current] + e.cost) {
				dist[e.to] = dist[current] + e.cost;
				pre[e.to] = G[current][i];
				a[e.to] = min(a[current], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
	if (dist[T] == INF) return false;
	flow += a[T];
	cost += a[T] * dist[T];
	for (int u = T; u != S; u = edges[pre[u]].from) {
		edges[pre[u]].flow += a[T];
		edges[pre[u] ^ 1].flow -= a[T];
	}
	return true;
}

int solve() {
	memset(pre, 0, sizeof(pre));
	memset(a, 0, sizeof(a));
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	return cost;
}

int main() {
	while (~scanf("%d %d", &n, &k)) {
		for (int i = 0; i <= T; i++)
			G[i].clear();
		edges.clear();
		int num;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &num);
				int id = i * n + j;
				// x :id * 2
				// x':id * 2 + 1
				addEdge(id * 2, id * 2 + 1, 1, -num); // x -> x' : (cap:1, cost:-num)
				addEdge(id * 2, id * 2 + 1, k - 1, 0); // x -> x' : (cap:k - 1, cost:0)
				if (i) addEdge((id - n) * 2 + 1, id * 2, k, 0);
				if (j) addEdge((id - 1) * 2 + 1, id * 2, k, 0);
			}
		}
		addEdge(S, 0, k, 0);
		addEdge((n * n - 1) * 2 + 1, T, k, 0);
		int ans = solve();
		printf("%d\n", -ans);
	}
	return 0;
}
