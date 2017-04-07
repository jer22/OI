#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int arr[1005][1005], dis[1005][1005];
int to[1005];
char vis[1005];
int dfn[1005];
vector<int> edges[1005];
int dfs1(int x, char co, int p) {
	vis[x] = co;
	dfn[x] = p;
	if (vis[to[x]] == co) return p - dfn[to[x]] + 1;
	else if (vis[to[x]]) return 0;
	return dfs1(to[x], co, p + 1);
}

int dfs(int x) {
	int p = 0;
	for (auto nex : edges[x])
		p = max(p, dfs(nex));
	return p + 1;
}

int main() {
	freopen("c.in", "r", stdin);
	freopen("ou", "w", stdout);
	int T;
	scanf("%d", &T);
	int n;

	for (int cas = 1; cas <= T; cas++) {
		cin >> n;
		printf("Case #%d: ", cas);
		memset(arr, 0x3f, sizeof(arr));
		memset(dis, 0x3f, sizeof(dis));
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1, x; i <= n; i++) {
			scanf("%d", &x);
			to[i] = x;
			edges[x].push_back(i);
		}
		memset(vis, 0, sizeof(vis));
		int ans1 = 0;
		int cc = 0;
		memset(dfn, 0, sizeof(dfn));
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) ans1 = max(ans1, dfs1(i, ++cc, 1));
		}
		memset(vis, 0, sizeof(vis));
		vector<pair<int, int> > ff;
		for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j)
			if (to[i] == j && to[j] == i) ff.push_back({i, j});
		int ans2 = 0;
		for (auto p : ff) {
			int a = p.first, b = p.second;
			int t1 = 0, t2 = 0;
			for (auto x : edges[a]) if (x != b) t1 = max(t1, dfs(x));
			for (auto x : edges[b]) if (x != a) t2 = max(t2, dfs(x));
			ans2 += t1 + t2 + 2;
		}
		cout << max(ans1, ans2) << endl;
	}


	return 0;
}
