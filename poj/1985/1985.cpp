#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
vector<Edge> edges[40005];
int dp[40005];
int dist[40005];

int dfs(int v, int pre) {
	dp[v] = v;
	dist[v] = 0;
	for (int i = 0; i < edges[v].size(); i++) {
		Edge e = edges[v][i];
		if (e.to == pre) continue;
		dfs(e.to, v);
		if (dist[e.to] + e.v > dist[v]) {
			dist[v] = dist[e.to] + e.v;
			dp[v] = dp[e.to];
		}
	}
	return dist[v];
}

int main() {
	freopen("1985.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		int a, b, c;
		char op[5];
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %d %s", &a, &b, &c, op);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		dfs(1, 0);
		int ans = dfs(dp[1], 0);
		printf("%d\n", ans);
	}
	return 0;
}
