#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

#define INF 0x3f3f3f3f

using namespace std;

int n, m, t;
int num, cnt;
vector<int> edges[4005];
stack<int> s;
int dfn[4005];
int low[4005];
int vis[4005];
int col[4005];

void dfs(int u) {
	s.push(u);
	vis[u] = 1;
	dfn[u] = low[u] = ++cnt;
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		num++;
		do {
			t = s.top();
			s.pop();
			vis[t] = 0;
			col[t] = num;
		} while (t != u);
	}
}

void tarjan() {
	num = cnt = 0;
	while (!s.empty()) s.pop();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(col, 0, sizeof(col));
	for (int i = 1; i <= n << 1; i++)
		if (!dfn[i]) dfs(i);
}

bool solve() {
	tarjan();
	for (int i = 1; i <= n; i++)
		if (col[i] == col[i + n]) return false;
	return true;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 0; i <= n << 1; i++)
			edges[i].clear();
		int a, b;
		int aa, bb;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			aa = abs(a), bb = abs(b);
			if (a > 0 && b > 0) {
				edges[aa + n].push_back(bb);
				edges[bb + n].push_back(aa);
			}
			if (a < 0 && b < 0) {
				edges[aa].push_back(bb + n);
				edges[bb].push_back(aa + n);
			}
			if (a > 0 && b < 0) {
				edges[aa + n].push_back(bb + n);
				edges[bb].push_back(aa);
			}
			if (a < 0 && b > 0) {
				edges[aa].push_back(bb);
				edges[bb + n].push_back(aa + n);
			}
		}
		bool ans = solve();
		cout << ans << endl;
	}
	return 0;
}
