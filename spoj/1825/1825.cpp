#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200005;

struct E{
	int to, v;
	E() {}
	E(int a, int b) : to(a), v(b) {}
};

int n, k, m;
int col[MAXN];
vector<E> edges[MAXN];
bool vis[MAXN];
int sz_down[MAXN];
void dfs(int x, int fa) {
	sz_down[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == fa) continue;
		if (vis[nex]) continue;
		dfs(nex, x);
		sz_down[x] += sz_down[nex];
	}
}
void dfs1(int x, int fa, int &max_num, int &idx, int root) {
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i].to;
		if (nex == fa) continue;
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
int ans = 0;
int dis[MAXN], dep[MAXN];

bool operator < (E a, E b) {
	return a.v < b.v;
}

int caldeep(int x, int fa = 0) {
	int mxdeep = dep[x];
	for (int i = 0; i < edges[x].size(); i++) {
		E e = edges[x][i];
		if (vis[e.to] || e.to == fa) continue;
		dis[e.to] = dis[x] + e.v;
		dep[e.to] = dep[x] + col[e.to];
		mxdeep = max(mxdeep, caldeep(e.to, x));
	}
	return mxdeep;
}

int now[MAXN], pre[MAXN];

void cal(int x, int fa = 0) {
	now[dep[x]] = max(now[dep[x]], dis[x]);
	for (int i = 0; i < edges[x].size(); i++) {
		E e = edges[x][i];
		if (vis[e.to] || e.to == fa) continue;
		cal(e.to, x);
	}
}

void solve(int x) {
	vis[x] = 1;
	if (col[x]) k--;
	vector<E> es;
	for (int i = 0; i < edges[x].size(); i++) {
		E e = edges[x][i];
		if (vis[e.to]) continue;
		dis[e.to] = e.v;
		dep[e.to] = col[e.to];
		es.push_back(E(e.to, caldeep(e.to)));
	}
	sort(es.begin(), es.end());

	for (int i = 0; i < es.size(); i++) {
		E e = es[i];
		if (vis[e.to]) continue;
		cal(e.to);
		int cur = 0;
		if (i) {
			for (int j = e.v; j >= 0; j--) {
				while (cur + j < k && cur < es[i - 1].v)
					cur++, pre[cur] = max(pre[cur], pre[cur - 1]);
				if (cur + j <= k) ans = max(ans, pre[cur] + now[j]);
			}	
		}
		if (i != es.size() - 1) {
			for (int j = 0; j <= e.v; j++) {
				pre[j] = max(pre[j], now[j]);
				now[j] = 0;
			}
		}
		else {
			for (int j = 0; j <= e.v; j++) {
				if (j <= k) ans = max(ans, max(pre[j], now[j]));
				pre[j] = now[j] = 0;
			}
		}
		
	}

	if (col[x]) k++;
	for (int i = 0; i < edges[x].size(); i++) {
		E e = edges[x][i];
		if (!vis[e.to]) solve(getroot(e.to));
	}
}

int main() {
	// freopen("1825.in", "r", stdin);
	scanf("%d %d %d", &n, &k, &m);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d", &a);
		col[a] = 1;
	}
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(E(b, c));
		edges[b].push_back(E(a, c));
	}
	solve(getroot(1));
	printf("%d\n", ans);


	return 0;
}
