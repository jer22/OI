#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), cap(c) {}
};

int n, m, t;
vector<Edge> edges;
vector<int> G[205];
Edge E[40005];

void addEdge(int u, int v) {
	edges.push_back(Edge(u, v, 1));
	edges.push_back(Edge(v, u, 1));
	int siz = edges.size();
	G[u].push_back(siz - 2);
	G[v].push_back(siz - 1);
}

void buildGraph(int x) {
	for (int i = 0; i <= n; i++)
			G[i].clear();
	edges.clear();
	for (int i = 0; i < m; i++) {
		if (E[i].cap <= x)
			addEdge(E[i].from, E[i].to);
	}
}

int cur[205];
int layer[205];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	layer[1] = 0;
	q.push(1);
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
	return layer[n] != -1;
}

int find(int x, int curFlow) {
	if (x == n || !curFlow) return curFlow;
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
		ans += find(1, INF);
	}
	return ans;
}

int solve(int l, int r) {
	int ans = -1;
	while (l <= r) {
		int mid = l + r >> 1;
		buildGraph(mid);
		if (dinic() >= t) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return ans;
}

int main() {
	freopen("2455.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &t)) {
		int l = INF, r = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &E[i].from, &E[i].to, &E[i].cap);
			l = min(l, E[i].cap);
			r = max(r, E[i].cap);
		}
		int ans = solve(l, r);
		cout << ans << endl;
	}
	return 0;
}
