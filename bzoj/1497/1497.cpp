#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define T (n + m + 1)

using namespace std;

struct Edge{
	int from, to, cap;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), cap(c) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[60005];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap));
	edges.push_back(Edge(to, from, 0));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

int cur[60005];
int layer[60005];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	layer[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int curFlow) {
	if (x == T || !curFlow) return curFlow;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(curFlow, e.cap)))) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			curFlow -= f;
			if (!curFlow) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(0, INF);
	}
	return ans;
}

int main() {
	freopen("1497.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		addEdge(i, T, x);
	}
	int a, b, c;
	int sum = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		sum += c;
		addEdge(0, i + n, c);
		addEdge(i + n, a, INF);
		addEdge(i + n, b, INF);
	}
	int ans = sum - dinic();
	printf("%d\n", ans);
	return 0;
}
