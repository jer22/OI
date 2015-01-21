#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n, m, t;
int cnt, num;
int dfn[4100];
int low[4100];
int vis[4100];
int col[4100];
stack<int> s;
int key[4100][2];
int door[4100][2];
vector<int> edges[4100];
void buildGraph(int x) {
	for (int i = 0; i <= n << 1; i++)
		edges[i].clear();
	for (int i = 0; i < n >> 1; i++) {
		edges[key[i][0]].push_back(key[i][1] + n);
		edges[key[i][1]].push_back(key[i][0] + n);
	}
	for (int i = 0; i < x; i++) {
		edges[door[i][0] + n].push_back(door[i][1]);
		edges[door[i][1] + n].push_back(door[i][0]);
	}
}

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

bool tarjan() {
	cnt = num = 0;
	while (!s.empty()) s.pop();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(col, 0, sizeof(col));
	for (int i = 0; i < n << 1; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 0; i < n; i++)
		if (col[i] == col[i + n]) return false;
	return true;
}

int solve() {
	int l = 0, r = m;
	int ans = 0;
		while (l <= r) {
		int mid = l + r >> 1;
		buildGraph(mid);
		if (tarjan()) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	return ans;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &key[i][0], &key[i][1]);
		for (int i = 0; i < m; i++)
			scanf("%d %d", &door[i][0], &door[i][1]);
		n <<= 1;
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
