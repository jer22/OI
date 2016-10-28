#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

struct Edge{
	int from, to;
	bool cut;
	Edge() {}
	Edge(int a, int b, bool c) : from(a), to(b), cut(c) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
int vis[MAXN];
int s[MAXM], top = 0;
int odd[MAXN], eve[MAXN], fa[MAXN];
int nodd = 0, neve = 0;

void dfs(int x, int pre, int d) {
	vis[x] = d;
	for (int i = 0; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if ((G[x][i] ^ pre) == 1) continue;
		if (vis[e.to]) {
			if (vis[e.to] > vis[x]) continue;
			if ((vis[x] - vis[e.to]) & 1)
				eve[x]++, eve[e.to]--, neve++;
			else {
				// cout << x << endl;
				odd[x]++, odd[e.to]--, nodd++;
			}
		} else {

			fa[e.to] = x;
			dfs(e.to, G[x][i], d + 1);
			odd[x] += odd[e.to];
			eve[x] += eve[e.to];
		}
	}
}

int main() {
	freopen("4238.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		edges.push_back(Edge(a, b, 0));
		edges.push_back(Edge(b, a, 0));
		G[a].push_back(edges.size() - 2);
		G[b].push_back(edges.size() - 1);
	}
	for (int i = 1; i <= n; i++)
		if (!vis[i]) dfs(i, m * 2 + 1, 1);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (fa[i] && (odd[i] == nodd) && !eve[i]) ans++;
	}
	// cout << nodd;
	if (nodd == 1) ans++;
	printf("%d\n", ans);
	return 0;
}
