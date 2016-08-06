#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 10005;

int T, n, m;
vector<int> edges[MAXN << 1];
int arr[MAXN];
int posi[MAXN][2];
int col[MAXN << 1], low[MAXN << 1], dfn[MAXN << 1];
bool vis[MAXN << 1];
int cnt = 0, num = 0;
stack<int> s;

int dfs(int u) {
	s.push(u);
	vis[u] = 1;
	++cnt;
	low[u] = dfn[u] = cnt;
	for (int j = 0; j < edges[u].size(); j++) {
		int v = edges[u][j];
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (low[u] == dfn[u]) {
		int t;
		num++;
		do {
			t = s.top();
			col[t] = num;
			s.pop();
			vis[t] = 0;
		}
		while (t != u);
	}
}

void tarjan() {
	while (!s.empty()) s.pop();
	for (int i = 1; i <= n << 1; i++)
		col[i] = low[i] = dfn[i] = vis[i] = 0;
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
	freopen("c.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			if (arr[i] == 1) {
				posi[i][0] = 1;
				posi[i][1] = 2;
			} else if (arr[i] == 2) {
				posi[i][0] = 2;
				posi[i][1] = 3;
			} else {
				posi[i][0] = 1;
				posi[i][1] = 3;
			}
		}
		for (int i = 1; i <= n << 1; i++)
			edges[i].clear();
		int s, a, b;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d %d", &a, &b, &s);
			if (!s) {
				if (posi[a][0] != posi[b][0]) {
					edges[a].push_back(b + n);
					edges[b].push_back(a + n);
				}
				if (posi[a][0] != posi[b][1]) {
					edges[a].push_back(b);
					edges[b + n].push_back(a + n);
				}
				if (posi[a][1] != posi[b][0]) {
					edges[a + n].push_back(b + n);
					edges[b].push_back(a);
				}
				if (posi[a][1] != posi[b][1]) {
					edges[a + n].push_back(b);
					edges[b + n].push_back(a);
				}
			} else {
				if (posi[a][0] == posi[b][0]) {
					edges[a].push_back(b + n);
					edges[b].push_back(a + n);
				}
				if (posi[a][0] == posi[b][1]) {
					edges[a].push_back(b);
					edges[b + n].push_back(a + n);
				}
				if (posi[a][1] == posi[b][0]) {
					edges[a + n].push_back(b + n);
					edges[b].push_back(a);
				}
				if (posi[a][1] == posi[b][1]) {
					edges[a + n].push_back(b);
					edges[b + n].push_back(a);
				}
			}
		}
		bool ans = solve();
		if (!ans) printf("Case #%d: no\n", cas);
		else printf("Case #%d: yes\n", cas);
	}

		


	return 0;
}
