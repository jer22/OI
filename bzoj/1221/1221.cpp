#include <bits/stdc++.h>

#define INF 0X3f3f3f3f
#define MAXN 2005
#define S 0
#define T 2003

using namespace std;

struct Edge{
	int from, to, cap, flow, cost;
	Edge(int u, int v, int c, int f, int x)
		: from(u), to(v), cap(c), flow(f), cost(x) {}
};

int n, m;
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

int arr[MAXN], a, b, ff, fa, fb;
int main() {
	freopen("1221.in", "r", stdin);
	scanf("%d %d %d %d %d %d", &n, &a, &b, &ff, &fa, &fb);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		addEdge(0, i, arr[i], 0);
		addEdge(i + n, T, arr[i], 0);
	}
	for (int i = 1; i <= n; i++) {
		if (i + 1 <= n) addEdge(i, i + 1, INF, 0);
		if (i + a + 1 <= n) addEdge(i, i + a + 1 + n, INF, fa);
		if (i + b + 1 <= n) addEdge(i, i + b + 1 + n, INF, fb);
		addEdge(0, i + n, INF, ff);
	}
	int ans = minCostMaxFlow();
	printf("%d\n", ans);
	return 0;
}
