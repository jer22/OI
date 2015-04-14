#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define S n + 1
#define T n + 2
#define SS n + 3
#define TT n + 4
#define MAXN 105
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap, flow;
	Edge() {}
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int n, k, x;
vector<Edge> edges;
vector<int> G[MAXN];
bool vis[MAXN];

void addEdge(int s, int t, int c) {
	edges.push_back(Edge(s, t, c, 0));
	edges.push_back(Edge(t, s, 0, 0));
	G[s].push_back(edges.size() - 2);
	G[t].push_back(edges.size() - 1);
}

int cur[MAXN << 1], layer[MAXN << 1];
bool build(int s, int t) {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(s);
	layer[s] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < G[u].size(); i++) {
			Edge e = edges[G[u][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[u] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[t] != -1;
}

int find(int x, int t, int a) {
	if (x == t || !a) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to] && (f = find(e.to, t, min(a, e.cap - e.flow)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic(int s, int t) {
	int ans = 0;
	while (build(s, t)) {
		memset(cur, 0, sizeof(cur));
		ans += find(s, t, INF);
	}
	return ans;
}

void rebuild(int mid) {
	for (int i = 0; i < edges.size(); i++)
		edges[i].flow = 0;
	edges[edges.size() - 2].cap = mid;
}

bool check() {
	for (int i = 0; i < G[SS].size(); i++)
		if (edges[G[SS][i]].cap > edges[G[SS][i]].flow) return false;
	return true;
}

int main() {
	freopen("2502.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &x);
			addEdge(i, x, INF);
			addEdge(SS, x, 1);
			addEdge(i, TT, 1);
			vis[x] = 1;
		}
		if (!k) addEdge(i, T, INF);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) addEdge(S, i, INF);
	addEdge(T, S, INF);
	int l = 0, r = INF;
	while (l < r) {
		int mid = l + r >> 1;
		rebuild(mid);
		dinic(SS, TT);
		if (check()) r = mid;
		else l = mid + 1;
	}
	cout << l << endl;

	return 0;
}
