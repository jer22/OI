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
	int from, to, cap, flow;
	Edge() {}
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int n, np, nc, m;
vector<Edge> edges;
vector<int> G[105];
void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap, 0));
	edges.push_back(Edge(to, from, 0, 0));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

int cur[105];
int layer[105];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int curflow) {
	if (x == T || !curflow) 
		return curflow;
	int f, flow = 0;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(curflow, e.cap - e.flow)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			curflow -= f;
			if (!curflow) break;
		}
	}
	return flow;
}

int dinic() {
	int maxflow = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		maxflow += find(0, INF);
	}
	return maxflow;
}

int main() {
	while (~scanf("%d %d %d %d", &n, &np, &nc, &m)) {
		char t;
		int a, b, c;
		for (int i = 0; i <= n; i++)
			G[i].clear();
		edges.clear();
		for (int i = 0; i < m; i++) {
			cin >> t >> a >> t >> b >> t >> c;
			addEdge(a + 1, b + 1, c);
		}
		for (int i = 0; i < np; i++) {
			cin >> t >> a >> t >> b;
			addEdge(0, a + 1, b);
		}
		for (int i = 0; i < nc; i++) {
			cin >> t >> a >> t >> b;
			addEdge(a + 1, T, b);
		}
		int ans = dinic();
		printf("%d\n", ans);
	}
	return 0;
}
