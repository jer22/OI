#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400005;

struct Edge{
	int from, to;
	bool cut, dir;
	Edge() {}
	Edge(int a, int b, int c = 0, int d = 0) : from(a), to(b), cut(c), dir(d) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN << 1];
int dfn[MAXN], low[MAXN];
int cnt = 0, num = 0;
int siz[MAXN];

void tarjan(int x, int pre) {
	dfn[x] = low[x] = ++cnt;
	for (int i = 0; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (e.to == pre) continue;
		if (!dfn[e.to]) {
			tarjan(e.to, x);
			low[x] = min(low[x], low[e.to]);
			if (low[e.to] > dfn[x]) {
				e.cut = edges[G[x][i] ^ 1].cut = 1;
			}
		} else low[x] = min(low[x], dfn[e.to]);
	}
}

bool vis[MAXN << 1];
void dfs(int x, int co) {
	vis[x] = 1;
	siz[co]++;
	for (int i = 0; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (vis[e.to] || e.cut) continue;
		dfs(e.to, co);
	}
}

void getdir(int x, int pre, int flag) {
	for (int i = 0; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (vis[G[x][i]] || vis[G[x][i] ^ 1]) continue;
		vis[G[x][i]] = vis[G[x][i] ^ 1] = 1;
		if (e.cut) {
			edges[G[x][i] ^ 1].dir = 1;
			getdir(e.to, x, 1);
		} else {
			edges[G[x][i] ^ flag].dir = 1;
			getdir(e.to, x, flag);
		}
	}
}

int main() {
	freopen("f.in", "r", stdin);
	cin >> n >> m;
	int a, b;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		edges.push_back(Edge(a, b));
		edges.push_back(Edge(b, a));
		G[a].push_back(edges.size() - 2);
		G[b].push_back(edges.size() - 1);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) tarjan(i, i);
	int mx = 0, id = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			num++;
			dfs(i, num);
			if (siz[num] > mx) {
				mx = siz[num];
				id = i;
			}
		}
	}
	memset(vis, 0, sizeof(vis));
	getdir(id, id, 0);
	cout << mx << endl;
	for (int i = 0; i < m * 2; i++) {
		Edge e = edges[i];
		if (e.dir) cout << e.from << ' ' << e.to << endl;
	}

	return 0;
}
