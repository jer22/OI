#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int from, to, v;
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
	bool operator < (const Edge &e) const {
		return v < e.v;
	}
};

int n;
vector<Edge> edges;
vector<Edge> tree[2005];
int arr[2005][2005];
int parent[2005];
int father[2005];
int vis[2005];
int lca[2005][2005];
int dp[2005];

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

int getFather(int r) {
	if (r == father[r]) return r;
	else return getFather(father[r]);
}

void dfs(int x) {
	vis[x] = 1;
	for (int i = 0; i < tree[x].size(); i++) {
		Edge e = tree[x][i];
		if (!vis[e.to]) {
			dfs(e.to);
			father[e.to] = x;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vis[i] && !lca[i][x]) {
			lca[i][x] = lca[x][i] = getFather(i);
		}
	}
}

void DP(int x, int pre) {
	for (int i = 0; i < tree[x].size(); i++) {
		Edge e = tree[x][i];
		if (e.to == pre) continue;
		dp[e.to] = dp[x] + e.v;
		DP(e.to, x);
	}
}

int main() {
	// freopen("f.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		parent[i] = father[i] = i;
		for (int j = 1; j <= n; j++) {
			scanf("%d", &arr[i][j]);
			if ((i == j && arr[i][j]) || (i != j && !arr[i][j]) || (i > j && arr[i][j] != arr[j][i])) {
				printf("NO\n");
				return 0;
			}
			if (i < j)
				edges.push_back(Edge(i, j, arr[i][j]));
		}
	}
	sort(edges.begin(), edges.end());
	for (int i = 0; i < edges.size(); i++) {
		Edge e = edges[i];
		if (find(e.from) == find(e.to)) continue;
		else {
			un(e.from, e.to);
			tree[e.from].push_back(Edge(e.from, e.to, e.v));
			tree[e.to].push_back(Edge(e.to, e.from, e.v));
		}
	}
	dfs(1);
	DP(1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int dist = dp[i] + dp[j] - dp[lca[i][j]] * 2;
			if (dist != arr[i][j]) {
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	return 0;
}
