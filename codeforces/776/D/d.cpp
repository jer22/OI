#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, m, t;
int arr[MAXN];
int fuc[MAXN][2];
vector<int> edges[MAXN << 1];
stack<int> s;
int vis[MAXN << 1], dfn[MAXN << 1], low[MAXN << 1], col[MAXN << 1], cnt, num;
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
	for (int i = 1; i <= m << 1; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= m; i++)
		if (col[i] == col[i + m]) return false;
	return true;
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	for (int i = 1, a, x; i <= m; i++) {
		scanf("%d", &a);
		while (a--) {
			scanf("%d", &x);
			if (fuc[x][0]) fuc[x][1] = i;
			else fuc[x][0] = i;
		}
	}
	for (int i = 1; i <= n; i++) {
		// cout << fuc[i][0] << ' ' << fuc[i][1] << endl;
		if (!arr[i]) {
			edges[fuc[i][0]].push_back(fuc[i][1] + m);
			edges[fuc[i][1] + m].push_back(fuc[i][0]);
			edges[fuc[i][1]].push_back(fuc[i][0] + m);
			edges[fuc[i][0] + m].push_back(fuc[i][1]);
		} else {
			edges[fuc[i][0]].push_back(fuc[i][1]);
			edges[fuc[i][1]].push_back(fuc[i][0]);
			edges[fuc[i][0] + m].push_back(fuc[i][1] + m);
			edges[fuc[i][1] + m].push_back(fuc[i][0] + m);
		}
	}
	int ans = tarjan();
	if (ans) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}
