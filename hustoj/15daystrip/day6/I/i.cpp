#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 30015 << 1
#define S 2
#define T 0

using namespace std;

struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

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

int cas, n, m;

int main() {
	freopen("i.in", "r", stdin);
	scanf("%d", &cas);
	int a, b;
	while (cas--) {
		scanf("%d %d", &n, &m);
		edges.clear();
		for (int i = 0; i <= n << 1; i++)
			G[i].clear();
		for (int i = 1; i <= n; i++) {
			if (i == 2) addEdge(i, i + n, 2);
			else addEdge(i, i + n, 1);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			if (a > n || b > n) continue;
			addEdge(a + n, b, 1);
			addEdge(b + n, a, 1);
		}
		addEdge(1 + n, T, 1);
		addEdge(3 + n, T, 1);
		if (dinic() == 2) printf("YES\n");
		else printf("NO\n");
	}


	return 0;
}
