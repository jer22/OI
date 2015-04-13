#include <bits/stdc++.h>

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, tot, ans;
vector<Edge> edges[2048];
int max_son[2048];
void dfs1(int u) {
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i].to;
		dfs1(v);
		max_son[u] = max(max_son[u], max_son[v] + edges[u][i].v);
	}
}

void dfs2(int u, int len) {
	for (int i = 0; i < edges[u].size(); i++) {
		Edge e = edges[u][i];
		int t = max_son[e.to] + e.v;
		ans += len - t;
		// cout << len - (len - t + e.v) << endl;
		dfs2(e.to, t - e.v);
	}
}

int main() {
	// freopen("b.in", "r", stdin);
	cin >> n;
	int t;
	for (int i = 2; i <= (1 << n + 1) - 1; i++) {
		cin >> t;
		edges[i >> 1].push_back(Edge(i, t));
	}
	dfs1(1);
	tot = max_son[1];
	dfs2(1, tot);

	cout << ans << endl;
	return 0;
}
