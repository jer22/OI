#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 505
#define S 0
#define T 503

using namespace std;

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
	q.push(S);
	layer[S] = 0;
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
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
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
		flow += find(S, INF);
	}
	return flow;
}


int n, f, d;
int main() {
	freopen("g.in", "r", stdin);
	scanf("%d %d %d", &n, &f, &d);
	int a, b, t;
	for (int i = 1; i <= n; i++) {
		addEdge(i, i + n, 1);
		scanf("%d %d", &a, &b);
		for (int j = 0; j < a; j++) {
			scanf("%d", &t);
			addEdge(n * 2 + t, i, 1);
		}
		for (int j = 0; j < b; j++) {
			scanf("%d", &t);
			addEdge(i + n, 2 * n + f + t, 1);
		}
	}
	for (int i = 1; i <= f; i++)
		addEdge(0, n * 2 + i, 1);
	for (int i = 1; i <= d; i++)
		addEdge(n * 2 + f + i, T, 1);
	printf("%d\n", dinic());

	return 0;
}
