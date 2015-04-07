#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 10005;

int n, m, t;
vector<int> edges[MAXN];
int cnt = 0, num = 0;
int dfn[MAXN], low[MAXN], col[MAXN];
bool vis[MAXN];
stack<int> s;

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

int siz[MAXN];
int tarjan() {
	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= n; i++)
		siz[col[i]]++;
	for (int i = 1; i <= num; i++)
		if (siz[i] > 1) ans++;
	return ans;
}

int main() {
	freopen("1654.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v);
		edges[u].push_back(v);
	}
	int ans = tarjan();
	printf("%d\n", ans);

	return 0;
}
