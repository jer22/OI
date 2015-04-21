#include <bits/stdc++.h>

#define INF 0x7f7f7f7f
#define T 1001

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[1005];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

int dist[1005], pre[1005], f[1005];
bool vis[1005];
bool spfa(int &flow, int &cost) {
	memset(dist, 0x7f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[0] = 0;
	vis[0] = 1;
	pre[0] = 0;
	f[0] = INF;
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			Edge &e = edges[G[cur][i]];
			if (e.cap > e.flow && dist[cur] + e.cost < dist[e.to]) {
				dist[e.to] = dist[cur] + e.cost;
				pre[e.to] = G[cur][i];
				f[e.to] = min(f[cur], e.cap - e.flow);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
	if (dist[T] == INF) return false;
	flow += f[T];
	cost += dist[T] * f[T];
	for (int i = T; i; i = edges[pre[i]].from) {
		edges[pre[i]].flow += f[T];
		edges[pre[i] ^ 1].flow -= f[T];
	}
	return true;
}

int mcmf() {
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	return cost;
}

int arr[105][105];
int main() {
	freopen("1070.in", "r", stdin);
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%d", &arr[i][j]);
	for (int i = 1; i <= n; i++)
		addEdge(0, i, 1, 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= n; k++)
				addEdge(i, j * n + k, 1, k * arr[i][j]);
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			addEdge(i * n + j, T, 1, 0);
	double ans = double(mcmf());
	ans /= n;
	printf("%.2f\n", ans);
	return 0;
}
