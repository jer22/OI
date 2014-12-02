#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXV 110
#define INF 0x3f3f3f3f
#define T 105

using namespace std;

struct Edge {
	int from, to, cap, flow;
};

int V, E, m;
vector<Edge> edges;
vector<int> G[MAXV];
int layer[MAXV];

void addEdge(int from, int to, int cap) {
	Edge temp;
	temp.from = from;
	temp.to = to;
	temp.cap = cap;
	temp.flow = 0;
	edges.push_back(temp);
	temp.from = to;
	temp.to = from;
	temp.cap = 0;
	temp.flow = 0;
	edges.push_back(temp);
	int E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(1);
	layer[1] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < G[v].size(); i++) {
			Edge &e = edges[G[v][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[v] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int v, int cur) {
	if (v == T || !cur) return cur;
	int flow = 0;
	int f;
	for (int i = 0; i < G[v].size(); i++) {
		Edge &e = edges[G[v][i]];
		if (layer[e.to] == layer[v] + 1
			&& (f = find(e.to, min(cur, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[v][i] + 1].flow -= f;
			flow += f;
			cur -= f;
			if (!cur) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build())
		ans += find(1, INF);
	return ans;
}

int main() {
	freopen("p1524.in", "r", stdin);
	scanf("%d %d", &V, &E);
	int a, b, w;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &w);
		addEdge(a, b, w);
		addEdge(b, a, w);
	}
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &w);
		addEdge(w, T, INF);
	}
	int ans = dinic();
	printf("%d\n", ans);
	return 0;
}
