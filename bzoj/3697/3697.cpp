#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
bool vis[MAXN];
int sz_down[MAXN];
vector<Edge> edges[MAXN];
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

int pre[MAXN << 1][2], now[MAXN << 1][2];
int dis[MAXN], cnt[MAXN << 1], deep[MAXN];
set<int> s;
int cal(int x, int fa = 0) {
	int mxdeep = deep[x];
	if (cnt[dis[x]]) now[dis[x]][1]++;
	else now[dis[x]][0]++;
	cnt[dis[x]]++;
	// s.insert(dis[x]);
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to] || e.to == fa) continue;
		dis[e.to] = dis[x] + e.v;
		deep[e.to] = deep[x] + 1;
		mxdeep = max(mxdeep, cal(e.to, x));
	}
	cnt[dis[x]]--;
	return mxdeep;
}
void clear(int x, int fa, int d) {
	pre[d][0] = pre[d][1] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to] || e.to == fa) continue;
		clear(e.to, x, d + e.v);
	}
}
long long solve(int x) {
	vis[x] = 1;
	long long ans = 0;
	pre[n][0] = 1;
	int mx = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to]) continue;
		dis[e.to] = e.v + n;
		deep[e.to] = 1;
		// s.clear();s
		int mxdeep = cal(e.to);
		mx = max(mx, mxdeep);
		ans += now[n][0] * (pre[n][0] - 1);
		for(int j = -mxdeep; j <= mxdeep; j++)
			ans += pre[n - j][1] * now[n + j][1] + pre[n - j][0] * now[n + j][1] + pre[n - j][1] * now[n + j][0];
		for(int j = n - mxdeep; j <= n + mxdeep; j++) {
			pre[j][0] += now[j][0];
			pre[j][1] += now[j][1];
			now[j][0] = now[j][1] = 0;
		}
	}
	for(int i = n - mx; i <= n + mx; i++)
		pre[i][0] = pre[i][1] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (vis[e.to]) continue;
		ans += solve(getroot(e.to));
	}
	return ans;
}

int main() {
	freopen("3697.in", "r", stdin);
	scanf("%d", &n);
	int a, b, c;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (!c) c = -1;
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	long long ans = solve(getroot(1));
	printf("%lld\n", ans);


	return 0;
}
