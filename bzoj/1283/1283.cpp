#include <bits/stdc++.h>

#define MAXN 2005
#define T 2003
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int a, int b, int c, int d, int e)
		: from(a), to(b), cap(c), flow(d), cost(e) {}
};

int n, m, K;
int arr[20005];
vector<Edge> edges;
vector<int> G[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

int dist[MAXN];
bool vis[MAXN];
int pre[MAXN];
int f[MAXN];
void spfa(int &flow, int &cost) {
	memset(dist, 0x3f, sizeof(dist));
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
		vis[cur] = 0;
	}
	flow += f[T];
	cost += f[T] * dist[T];
	for (int i = T; i; i = edges[pre[i]].from) {
		edges[pre[i]].flow += f[T];
		edges[pre[i] ^ 1].flow -= f[T];
	}
}

int mcmf() {
	int flow = 0, cost = 0;
	for (int i = 0; i < K; i++)
		spfa(flow, cost);
	return cost;
}

int main() {
	freopen("1283.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		addEdge(0, i, INF, 0);
		addEdge(i + n, T, INF, 0);
		addEdge(i, i + n, 1, -arr[i]);
		if (i > 1) addEdge(i, i - 1, INF, 0);
		if (i > m) addEdge(i + n, i - m, INF, 0);
	}
	int ans = mcmf();
	printf("%d\n", -ans);

	return 0;
}
