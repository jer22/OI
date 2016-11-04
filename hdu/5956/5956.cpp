#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int T, n;
long long P;
vector<int> G[MAXN];
vector<Edge> edges;
long long dp[MAXN], dist[MAXN];
int deep[MAXN], nex[MAXN];

void dfspre(int x, int pre) {
	dp[x] = dist[x] * dist[x];
	for (int i = 0; i < G[x].size(); i++) {
		Edge e = edges[G[x][i]];
		if (e.to == pre) continue;
		deep[e.to] = deep[x] + 1;
		dist[e.to] = dist[x] + e.v;
		dfspre(e.to, x);
	}
}

int last[MAXN], top = 0;
long long ans;
void dfs(int x, int pre) {
	if (deep[x] >= 2) {
		int idx = last[top];
		for (int i = last[top]; i != x; i = nex[i]) {
			long long nw = (dist[x] - dist[i]) * (dist[x] - dist[i]) + dp[i] + P;
			if (nw < dp[x]) {
				dp[x] = nw;
				idx = i;
			}
		}
		last[++top] = idx;
	} else last[++top] = x;
	ans = max(ans, dp[x]);
	for (int i = 0; i < G[x].size(); i++) {
		Edge e = edges[G[x][i]];
		if (e.to == pre) continue;

		nex[x] = e.to;
		dfs(e.to, x);
		top--;
	}
}

int main() {
	freopen("5956.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lld", &n, &P);
		edges.clear();
		for (int i = 1; i <= n; i++)
			G[i].clear();
		int a, b;
		long long c;
		for (int i = 1; i < n; i++) {
			scanf("%d %d %lld", &a, &b, &c);
			edges.push_back(Edge(b, c));
			edges.push_back(Edge(a, c));
			G[a].push_back(edges.size() - 2);
			G[b].push_back(edges.size() - 1);
		}
		dfspre(1, 1);
		top = 0, ans = 0;
		dfs(1, 1);
		printf("%lld\n", ans);
	}
	return 0;
}
