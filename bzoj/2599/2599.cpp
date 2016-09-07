#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int MAXM = 1000005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
int sz_down[MAXN];
vector<Edge> edges[MAXN];
bool vis[MAXN];

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

int mi[MAXM], dis[MAXN], dep[MAXN];
int cal(int x, int pre, int v) {
	dis[x] = dis[pre] + v;
	dep[x] = dep[pre] + 1;
	int ans = 0x3f3f3f3f;
	if (dis[x] <= m) ans = min(ans, dep[x] + mi[m - dis[x]]);
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to] || e.to == pre) continue;
		ans = min(ans, cal(e.to, x, e.v));
	}
	return ans;
}
void update(int x, int pre = 0) {
	if (dis[x] <= m) mi[dis[x]] = min(mi[dis[x]], dep[x]);
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to] || e.to == pre) continue;
		update(e.to, x);
	}
}
void clear(int x, int pre = 0) {
	if (dis[x] <= m) mi[dis[x]] = 0x3f3f3f3f;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to] || e.to == pre) continue;
		clear(e.to, x);
	}
}

int solve(int x) {
	int ans = 0x3f3f3f3f;
	vis[x] = 1;
	mi[0] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to]) continue;
		ans = min(ans, cal(e.to, 0, e.v));
		update(e.to);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to]) continue;
		clear(e.to);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to]) continue;
		ans = min(ans, solve(getroot(e.to)));
	}
	return ans;
}

int main() {
	freopen("2599.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		a++, b++;
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	memset(mi, 0x3f, sizeof(mi));
	int ans = solve(getroot(1));
	if (ans == 0x3f3f3f3f) ans = -1;
	cout << ans << endl;


	return 0;
}
