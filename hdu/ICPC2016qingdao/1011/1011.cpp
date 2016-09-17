#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 1005;

struct E{
	int to, v;
	E() {}
	E(int a, int b) : to(a), v(b) {}
};

int T;
int n, m;
vector<E> es[MAXN];
vector<E> pre[MAXN];
int dist[MAXN], vis[MAXN];
int val[MAXN][MAXN];

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(n);
	layer[n] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[1] != -1;
}

int find(int x, int a) {
	if (x == 1 || a == 0) return a;
	int flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(n, INF);
	}
	return flow;
}

void build_graph(int x) {
	vis[x] = 1;
	for (int i = 0; i < pre[x].size(); i++) {
		E e = pre[x][i];
		addEdge(x, e.to, e.v);
		if (!vis[e.to]) build_graph(e.to);
	}
}

void bfs() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[1] = 0;
	vis[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < es[cur].size(); i++) {
			E nex = es[cur][i];
			if (dist[cur] + 1 == dist[nex.to]) {
				pre[nex.to].push_back(E(cur, nex.v));
			} else if (dist[cur] + 1 < dist[nex.to]) {
				dist[nex.to] = dist[cur] + 1;
				pre[nex.to].clear();
				pre[nex.to].push_back(E(cur, nex.v));
				if (!vis[nex.to]) {
					vis[nex.to] = 1;
					q.push(nex.to);
				}
			}
		}
	}
}

int main() {
	freopen("1011.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			es[i].clear();
			pre[i].clear();
		}
		int a, b, c;
		// memset(val, 0, sizeof(val));
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			es[a].push_back(E(b, c));
			es[b].push_back(E(a, c));
		}
		bfs();
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= n; i++)
			G[i].clear();
		edges.clear();
		build_graph(n);
		printf("%d\n", dinic());
	}


	return 0;
}
