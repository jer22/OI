#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, K;
vector<Edge> G[MAXN];
int dist[MAXN], vis[MAXN], pre[MAXN];

void spfa() {
	memset(dist, 0x3f, sizeof(dist));
	dist[1] = 0;
	vis[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		for (int i = 0; i < G[cur].size(); i++) {
			Edge e = G[cur][i];
			if ((dist[e.to] == dist[cur] + e.v) && cur < pre[e.to]) pre[e.to] = cur;
			if (dist[e.to] > dist[cur] + e.v) {
				dist[e.to] = dist[cur] + e.v;
				pre[e.to] = cur;
				if (!vis[e.to]) q.push(e.to);
			}
		}
	}
}

vector<Edge> edges[MAXN];
void buildGraph() {
	memset(vis, 0, sizeof(vis));
	vis[1] = 1;
	queue<int> q;
	q.push(1);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < G[cur].size(); i++) {
			Edge e = G[cur][i];
			if (vis[e.to]) continue;
			if (pre[e.to] == cur) {
				edges[cur].push_back(Edge(e.to, e.v));
				edges[e.to].push_back(Edge(cur, e.v));
				vis[e.to] = 1;
				q.push(e.to);
			}
		}
	}
}
int sz_down[MAXN];
void dfs(int x, int pre) {
	sz_down[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (vis[nex]) continue;
		dfs(nex, x);
		sz_down[x] += sz_down[nex];
	}
}
void dfs1(int x, int pre, int &max_num, int &idx, int root) {
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == pre) continue;
		if (vis[nex]) continue;
		dfs1(nex, x, max_num, idx, root);
		cnt = max(cnt, sz_down[nex]);
	}
	cnt = max(cnt, sz_down[root] - sz_down[x]);
	if (cnt < max_num) {
		max_num = cnt;
		idx = x;
	}
}
int getroot(int x) {
	int max_num = 0x3f3f3f3f, idx;
	dfs(x, x);
	dfs1(x, x, max_num, idx, x);
	return idx;
}

int f[MAXN][2], g[MAXN][2];
int ans1 = 0, ans2 = 0;
void fuck(int x, int pre, int deep, int len) {
	if (len > g[deep][0]) {
		g[deep][0] = len;
		g[deep][1] = 0;
	}
	if (len == g[deep][0]) g[deep][1]++;

	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if ((e.to == pre) || vis[e.to]) continue;
		fuck(e.to, x, deep + 1, len + e.v);
	}
}

void solve(int root) {

	vis[root] = 1;
	dfs(root, root);
	for (int i = 0; i <= sz_down[root]; i++)
		f[i][0] = f[i][1] = 0;
	f[0][1] = 1;
	for (int i = 0; i < edges[root].size(); i++) {
		Edge e = edges[root][i];
		if (vis[e.to]) continue;
		for (int j = 0; j <= sz_down[e.to]; j++)
			g[j][0] = g[j][1] = 0;
		fuck(e.to, root, 1, e.v);
		for (int j = 1; j <= min(K, sz_down[e.to]); j++) {
			if (g[j][0] + f[K - j - 1][0] > ans1)
				ans1 = g[j][0] + f[K - j - 1][0], ans2 = 0;
			if (g[j][0] + f[K - j - 1][0] == ans1) {

				ans2 += g[j][1] * f[K - j - 1][1];
			}
		}
		for (int j = 1; j <= sz_down[e.to]; j++) {
			if (g[j][0] > f[j][0])
				f[j][0] = g[j][0], f[j][1] = 0;
			if (g[j][0] == f[j][0]) {
				f[j][1] += g[j][1];
			}
		}
	}

	for (int i = 0; i < edges[root].size(); i++) {
		int nex = edges[root][i].to;
		if (vis[nex]) continue;
		solve(getroot(nex));
	}
}

int main() {
	freopen("4016.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &K);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		G[a].push_back(Edge(b, c));
		G[b].push_back(Edge(a, c));
	}
	spfa();
	buildGraph();
	memset(vis, 0, sizeof(vis));
	solve(getroot(1));
	cout << ans1 << ' ' << ans2 << endl;

	return 0;
}
