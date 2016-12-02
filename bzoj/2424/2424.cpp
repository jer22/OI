#include <bits/stdc++.h>

#define S 0
#define T n + 1
#define INF LONG_LONG_MAX
#define MAXN 55

using namespace std;

struct Edge{
	int from, to;
	long long cap, flow, cost;
	Edge(int u, int v, long long c, long long f, long long x)
		: from(u), to(v), cap(c), flow(f), cost(x) {}
};

int n;
long long m, s;
vector<int> G[MAXN];
vector<Edge> edges;
bool done[MAXN];
int pre[MAXN];
long long dist[MAXN];
long long f[MAXN];

void addEdge(int from, int to, long long cap, long long cost) {
	edges.push_back(Edge(from, to, cap, 0, cost));
	edges.push_back(Edge(to, from, 0, 0, -cost));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

bool spfa(long long& flow, long long& cost) {
	for (int i = 0; i <= T; i++)
		dist[i] = INF;
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

long long minCostMaxFlow() {
	long long flow = 0, cost = 0;
	while(spfa(flow, cost));
	return cost;
}

int main() {
	freopen("2424.in", "r", stdin);
	scanf("%d %lld %lld", &n, &m, &s);
	long long a;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a);
		addEdge(i, T, a, 0);
		if (i < n) addEdge(i, i + 1, s, m);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a);
		addEdge(S, i, INF, a);
	}
	long long ans = minCostMaxFlow();
	printf("%lld\n", ans);
	return 0;
}
