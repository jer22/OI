#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n, m, t;
int flag[10002];
vector<int> edges[10002];
stack<int> s;
int dfn[10002];
int low[10002];
int vis[10002];
int col[10002];
int cnt, num;

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
	while (!s.empty()) s.pop();
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(col, 0, sizeof(col));
	cnt = num = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
}

int main() {
	freopen("2186.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
		}
		tarjan();
		memset(flag, 0, sizeof(flag));
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < edges[i].size(); j++)
				if (col[i] != col[edges[i][j]])
					flag[col[i]] = 1;
		int tot = 0;
		for (int i = 1; i <= num; i++)
			if (!flag[i]) tot++;
		if (tot != 1) printf("0\n");
		else {
			int ans = 0;
			for (int i = 1; i <= n; i++)
				if (!flag[col[i]]) ans++;
			printf("%d\n", ans);
		}
	}


	return 0;
}
