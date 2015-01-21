#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int T, n, m, t;
vector<int> edges[1005];
vector<int> tree[1005];
int dp[1005];
bool flag[1005][1005];
stack<int> s;
int dfn[1005];
int low[1005];
int vis[1005];
int col[1005];
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

int DP(int x) {
	if (dp[x] != -1) return dp[x];
	int ans = 0;
	for (int i = 0; i < tree[x].size(); i++) {
		int nex = tree[x][i];
		ans = max(ans, DP(nex));
	}
	dp[x] = ++ans;
	return ans;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i <= n; i++) {
			tree[i].clear();
			edges[i].clear();
		}
		int a, b;
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
		}
		tarjan();
		memset(flag, 0, sizeof(flag));
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < edges[i].size(); j++) {
				if (col[i] != col[edges[i][j]] && !flag[col[i]][col[edges[i][j]]]) {
					flag[col[i]][col[edges[i][j]]] = 1;
					tree[col[i]].push_back(col[edges[i][j]]);
				}
			}
		}
		memset(vis, 0, sizeof(vis));
		memset(dp, -1, sizeof(dp));
		int ans = 0;
		for (int i = 1; i <= num; i++)
			ans = max(ans, DP(i));
		if (ans == num) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
