#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define MAXN 2005
#define S 0
#define T n + n + 1

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
int dist[MAXN], pre[MAXN], a[MAXN];
bool vis[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}


bool spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[0] = 0;
	vis[0] = 1;
	pre[0] = 0;
	a[0] = INF;
	q.push(0);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			Edge &e = edges[G[cur][i]];
			if (e.cap > e.flow && dist[cur] + e.cost < dist[e.to]) {
				dist[e.to] = dist[cur] + e.cost;
				pre[e.to] = G[cur][i];
				a[e.to] = min(a[cur], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
	if (dist[T] == INF) return false;
	flow += a[T];
	cost += a[T] * dist[T];
	for (int i = T; i != S; i = edges[pre[i]].from) {
		edges[pre[i]].flow += a[T];
		edges[pre[i] ^ 1].flow -= a[T];
	}
	return true;
}

int mcmf() {
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	return cost;
}

int main() {
	freopen("1927.in", "r", stdin);
	cin >> n >> m;
	int x, y, z;
	for (int i = 1; i <= n; i++) {
		cin >> x;
		addEdge(0, i + n, 1, x);
		addEdge(0, i, 1, 0);
		addEdge(i + n, T, 1, 0);
	}
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;
		if (x > y) swap(x, y);
		addEdge(x, y + n, 1, z);
	}
	int ans = mcmf();
	cout << ans << endl;
	return 0;
}
