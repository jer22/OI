#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 205
#define S n + n + 1
#define T n + n + 2
#define SS n + n + 3
#define TT n + n + 4

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

int dist[MAXN];
bool vis[MAXN];
int pre[MAXN], a[MAXN];
bool spfa(int &flow, int &cost) {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[S] = 0;
	vis[S] = 1;
	pre[S] = 0;
	a[S] = INF;
	q.push(S);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < G[cur].size(); i++) {
			Edge &e = edges[G[cur][i]];
			if (e.cap > e.flow && dist[e.to] > dist[cur] + e.cost) {
				dist[e.to] = dist[cur] + e.cost;
				pre[e.to] = G[cur][i];
				a[e.to] = min(a[cur], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
	}
	if (dist[T] == INF) return false;
	flow += a[T];
	cost += dist[T] * a[T];
	for (int i = T; i != S; i = edges[pre[i]].from) {
		edges[pre[i]].flow += a[T];
		edges[pre[i] ^ 1].flow -= a[T];
	}
	return true;
}

int EK() {
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	return cost;
}

int main() {
	freopen("2055.in", "r", stdin);
	scanf("%d %d", &n, &m);
	addEdge(TT, SS, m, 0);
	int t;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &t);
		addEdge(S, i, t, 0);
		addEdge(i + n, T, t, 0);
		addEdge(i, TT, INF, 0);
		addEdge(SS, i + n, INF, 0);
	}
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			scanf("%d", &t);
			if (t != -1) addEdge(i, j + n, INF, t);
		}
	}
	int ans = EK();
	printf("%d\n", ans);
	return 0;
}
