#include <bits/stdc++.h>

#define S 0
#define T 103
#define MAXN 105
#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int x)
		: from(u), to(v), cap(c), flow(f), cost(x) {}
};

int n, m, k;
vector<int> G[MAXN];
vector<Edge> edges;
bool done[MAXN];
int dist[MAXN];
int pre[MAXN];
int f[MAXN];

void addEdge(int from, int to, int cap, int cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

bool spfa(int& flow, int& cost) {
	memset(dist, 0x3f, sizeof(dist));
	memset(done, 0, sizeof(done));
	dist[S] = 0;
	done[S] = 1;
	pre[S] = 0;
	f[S] = INF;
	queue<int> buff;
	buff.push(S);
	while(!buff.empty()) {
		int current = buff.front();
		buff.pop();
		done[current] = 0;
		for (int i = 0; i < G[current].size(); i++) {
			Edge& e = edges[G[current][i]];
			if (e.cap > e.flow && dist[e.to] > dist[current] + e.cost) {
				dist[e.to] = dist[current] + e.cost;
				pre[e.to] = G[current][i];
				f[e.to] = min(f[current], e.cap - e.flow);
				if (!done[e.to]) {
					done[e.to] = 1;
					buff.push(e.to);
				}
			}
		}
	}
	if (dist[T] == INF)
		return false;
	flow += f[T];
	cost += dist[T] * f[T];
	for (int u = T; u != S; u = edges[pre[u]].from) {
		edges[pre[u]].flow += f[T];
		edges[pre[u] ^ 1].flow -= f[T];
	}
	return true;
}

int minCostMaxFlow() {
	int flow = 0, cost = 0;
	while(spfa(flow, cost));
	return cost;
}

bool check() {
	for (int i = 0; i < edges.size(); i++)
		if (edges[i].to == T && edges[i].cap > edges[i].flow)
			return false;
	return true;
}

int cas;
int arr[MAXN];
int main() {
	freopen("3280.in", "r", stdin);
	scanf("%d", &cas);
	for (int c = 1; c <= cas; c++) {
		edges.clear();
		for (int i = 0; i <= T; i++)
			G[i].clear();
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			addEdge(i, T, arr[i], 0);
			addEdge(0, i + n, arr[i], 0);
			if (i < n) addEdge(i, i + 1, INF, 0);
		}
		int a, b;
		int tot = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &a, &b);
			tot += a;
			addEdge(0, 1, a, b);
		}
		for (int i = 1; i <= k; i++) {
			scanf("%d %d", &a, &b);
			for (int j = 1; j <= n; j++)
				if (j + a + 1 <= n) addEdge(j + n, j + a + 1, INF, b);
		}
		int ans = minCostMaxFlow();
		printf("Case %d: ", c);
		if (check()) printf("%d\n", ans);
		else printf("impossible\n");
	}

	return 0;
}
