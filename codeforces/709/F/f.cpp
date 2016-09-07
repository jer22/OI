#include <bits/stdc++.h>

#define S 0
#define T n + 1
#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 105;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, m;
vector<int> G[MAXN];
vector<Edge> edges;

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

int dist[MAXN], pre[MAXN], f[MAXN];
bool vis[MAXN];
bool spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[S] = 0;
	vis[S] = 1;
	pre[S] = 0;
	f[S] = INF;
	queue<int> q;
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
				f[e.to] = min(f[cur], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
	}
	if (dist[T] == INF) return false;
	flow += f[T];
	cost += dist[T] * f[T];
	for (int u = T; u != S; u = edges[pre[u]].from) {
		edges[pre[u]].flow += f[T];
		edges[pre[u] ^ 1].flow -= f[T];
	}
	return true;
}

int in[MAXN];
int main() {
	freopen("f.in", "r", stdin);
	cin >> n >> m;
	int a, b, c, d;
	int ans = 0;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c >> d;
		in[b] += d;
		in[a] -= d;
		if (d > c) {
			ans += d - c;
			addEdge(b, a, d - c, 0);
			addEdge(b, a, c, 1);
			addEdge(a, b, INF, 2);
		} else {
			addEdge(b, a, d, 1);
			addEdge(a, b, c - d, 1);
			addEdge(a, b, INF, 2);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (in[i] >= 0) {
			addEdge(S, i, in[i], 0);
		} else addEdge(i, T, -in[i], 0);
	}
	addEdge(n, 1, INF, 0);
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	ans += cost;
	cout << ans << endl;

	return 0;
}
