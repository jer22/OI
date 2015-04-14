#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define MAXN 305
#define INF 0x3f3f3f3f
#define S 0
#define T n + 1

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n;
vector<Edge> edges;
vector<int> G[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

int dist[MAXN], vis[MAXN], pre[MAXN], f[MAXN];
bool spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[S] = 0;
	vis[S] = 1;
	pre[S] = 0;
	f[S] = INF;
	q.push(S);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			Edge &e = edges[G[cur][i]];
			if (e.cap > e.flow && dist[cur] + e.cost < dist[e.to]) {
				dist[e.to] = dist[cur] + e.cost;
				pre[e.to] = G[cur][i];
				f[e.to] = min(f[cur], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
	if (dist[T] == INF) return false;
	flow += f[T];
	cost += f[T] * dist[T];
	for (int i = T; i != S; i = edges[pre[i]].from) {
		edges[pre[i]].flow += f[T];
		edges[pre[i] ^ 1].flow -= f[T];
	}
	return true;
}

int EK() {
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	return cost;
}

int main() {
	freopen("3876.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int k;
		scanf("%d", &k);
		int a, b;
		for (int j = 0; j < k; j++) {
			scanf("%d %d", &a, &b);
			addEdge(S, a, 1, b);
			addEdge(i, a, INF, b);
		}
		addEdge(i, T, k, 0);
		if (i != 1) addEdge(i, 1, INF, 0);
	}
	printf("%d\n", EK());
	return 0;
}
