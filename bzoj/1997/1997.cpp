#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

using namespace std;

int T, n, m;
pii es[10005];
int road[205], pos[205];
vector<int> edges[2005];
int cnt, num;
stack<int> s;
int dfn[2005], low[2005], col[2005], vis[2005];

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
	if (dfn[u] == low[u]) {
		int t;
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
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(col, 0, sizeof(col));
	memset(vis, 0, sizeof(vis));
	while (!s.empty()) s.pop();
	cnt = num = 0;
	for (int i = 1; i <= m * 2; i++)
		if (!dfn[i]) dfs(i);
	for (int i = 1; i <= m; i++) {
		if (col[i] == col[i + m]) return false;
	}
	return true;
}

int main() {
	freopen("1997.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= m; i++)
			cin >> es[i].first >> es[i].second;
		for (int i = 1; i <= n; i++) {
			cin >> road[i];
			pos[road[i]] = i;
		}
		if (m > 3 * n - 6) {
			cout << "NO" << endl;
			continue;
		}
		for (int i = 1; i <= 2004; i++)
			edges[i].clear();
		for (int i = 1; i <= m; i++) {
			int u = pos[es[i].first];
			int v = pos[es[i].second];
			if (u > v) swap(u, v);
			if (v - u == 1 || (u == 1 && v == n)) continue;
			for (int j = i + 1; j <= m; j++) {
				int x = pos[es[j].first];
				int y = pos[es[j].second];
				if (x > y) swap(x, y);
				if (y - x == 1 || (x == 1 && y == n)) continue;
				if ((u < x && v > x && v < y) || (x < u && u < y && y < v)) {
					edges[i].push_back(j + m);
					edges[j].push_back(i + m);
					edges[i + m].push_back(j);
					edges[j + m].push_back(i);
				}
			}
		}
		if (tarjan()) cout << "YES" << endl;
		else cout << "NO" << endl;
	}


	return 0;
}
