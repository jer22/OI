#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

#define INF LONG_LONG_MAX
#define MAXN 5005

using namespace std;

struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

int n, m, S, T;
vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

void addEdge(int from, int to, long long cap) {
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

long long find(int x, long long a) {
	if (x == T || a == 0) return a;
	long long flow = 0, f;
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

long long dinic() {
	long long flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, INF);
	}
	return flow;
}

int main() {
	// freopen("j.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	long long c;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	S = 1, T = n;
	printf("%lld\n", dinic());

	return 0;
}
