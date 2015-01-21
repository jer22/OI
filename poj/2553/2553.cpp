#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int n, m, t;
bool flag[5002];
vector<int> edges[5002];
stack<int> s;
int dfn[5002], low[5002];
int vis[5002];
int col[5002];
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
			col[t] = num;
			vis[t] = 0;
		} while (t != u);
	}
}

void tarjan() {
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(col, 0, sizeof(col));
	while (!s.empty()) s.pop();
	cnt = num = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
}

int main() {
	while (~scanf("%d", &n) && n) {
		scanf("%d", &m);
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
		vector<int> ans;
		for (int i = 1; i <= n; i++)
			if (!flag[col[i]])
				ans.push_back(i);
		int siz = ans.size();
		for (int i = 0; i < siz; i++)
			cout << ans[i] << " \n"[i == siz - 1];
	}
	return 0;
}
