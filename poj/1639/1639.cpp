#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#define INF 0x3f3f3f3f
#define MAXN 22

using namespace std;

struct Edge{
	int u, v, d;
	Edge() {}
	Edge(int a, int b, int c) : u(a), v(b), d(c) {}
	bool operator < (const Edge &e) const {
		return d < e.d;
	}
};

int n, m, k;
int cnt;
int ans;
int parent[MAXN];
map<string, int> nodes;
vector<Edge> edges;
Edge dp[MAXN];
int g[MAXN][MAXN];
bool tree[MAXN][MAXN];
int minEdge[MAXN];

int find(int p) {
	if (p == parent[p]) return parent[p];
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

void kruskal() {
	sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); i++) {
		int p = edges[i].u;
		int q = edges[i].v;
		if (p == 1 || q == 1) continue;
		if (find(p) != find(q)) {
			un(p, q);
			tree[p][q] = tree[q][p] = 1;
			ans += edges[i].d;
		}
	}
}

void dfs(int cur, int pre) {
	for (int i = 2; i <= cnt; i++) {
		if (i == pre || !tree[cur][i]) continue;
		if (dp[i].d == -1) {
			if (dp[cur].d > g[cur][i]) dp[i] = dp[cur];
			else {
				dp[i].u = cur;
				dp[i].v = i;
				dp[i].d = g[cur][i];
			}
		}
		dfs(i, cur);
	}
}

void solve() {
	int keyPoint[MAXN];
	for (int i = 2; i <= cnt; i++) {
		if (g[1][i] != INF) {
			int color = find(i);
			if (minEdge[color] > g[1][i]) {
				minEdge[color] = g[1][i];
				keyPoint[color] = i;
			}
		}
	}
	for (int i = 1; i <= cnt; i++) {
		if (minEdge[i] != INF) {
			m++;
			tree[1][keyPoint[i]] = tree[keyPoint[i]][1] = 1;
			ans += g[1][keyPoint[i]];
		}
	}
	for (int i = m + 1; i <= k; i++) {
		memset(dp, -1, sizeof(dp));
		dp[1].d = -INF;
		for (int j = 2; j <= cnt; j++)
			if (tree[1][j]) dp[j].d = -INF;
		dfs(1, -1);
		int idx, minnum = INF;
		for (int j = 2; j <= cnt; j++) {
			if (minnum > g[1][j] - dp[j].d) {
				minnum = g[1][j] - dp[j].d;
				idx = j;
			}
		}
		if (minnum >= 0) break;
		tree[1][idx] = tree[idx][1] = 1;
		tree[dp[idx].u][dp[idx].v] = tree[dp[idx].v][dp[idx].u] = 0;
		ans += minnum;
	}
}

void init() {
	memset(g, 0x3f, sizeof(g));
	memset(tree, 0, sizeof(tree));
	memset(minEdge, 0x3f, sizeof(minEdge));
	m = 0;
	cnt = 1;
	ans = 0;
	nodes["Park"] = 1;
	for (int i = 0; i < MAXN; i++)
		parent[i] = i;
}

int main() {
	freopen("1639.in", "r", stdin);
	scanf("%d", &n);
	string s1, s2;
	int d;
	init();
	for (int i = 1; i <= n; i++) {
		cin >> s1 >> s2 >> d;
		if (!nodes[s1]) nodes[s1] = ++cnt;
		if (!nodes[s2]) nodes[s2] = ++cnt;
		int u = nodes[s1], v = nodes[s2];
		edges.push_back(Edge(u, v, d));
		g[u][v] = g[v][u] = min(g[u][v], d);
	}
	scanf("%d", &k);
	kruskal();
	solve();
	printf("Total miles driven: %d\n", ans);
	return 0;
}
