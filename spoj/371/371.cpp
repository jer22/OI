#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define T (n + 1)

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n;
vector<int> G[1005];
vector<Edge> edges;
int pre[1005];
int a[1005];
int dist[1005];
bool vis[1005];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

bool spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[0] = 0;
	vis[0] = 1;
	pre[0] = -1;
	a[0] = INF;
	q.push(0);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge &e = edges[G[current][i]];
			if (e.cap > e.flow && dist[current] + e.cost < dist[e.to]) {
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
	for (int u = T; u != 0; u = edges[pre[u]].from) {
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
	freopen("371.in", "r", stdin);
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i <= T; i++)
			G[i].clear();
		edges.clear();
		int x;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			addEdge(0, i, x, 0);
			addEdge(i, T, 1, 0);
			addEdge(i, i % n + 1, INF, 1);
			addEdge(i % n + 1, i, INF, 1);
		}
		int ans = solve();
		printf("%d\n", ans);
	}

	return 0;
}
