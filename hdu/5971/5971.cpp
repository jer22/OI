#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1005;

int vis[MAXN];
vector<int> edges[MAXN];

bool dfs(int x, int c) {
	vis[x] = c;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (!vis[nex]) {
			if (!dfs(nex, c ^ 3)) return false;
		} else if (vis[nex] == c) return false;
	}
	return true;
}

int n, m, x, y;
int main() {
	freopen("5971.in", "r", stdin);
	while (~scanf("%d %d %d %d", &n, &m, &x, &y)) {
		int a, b;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}

		memset(vis, 0, sizeof(vis));
		bool flag = true;
		for (int i = 0; i < x; i++) {
			scanf("%d", &a);
			if (!vis[a]) if (!dfs(a, 1)) flag = false;
			if (vis[a] == 2) flag = false;
		}
		for (int i = 0; i < y; i++) {
			scanf("%d", &a);
			if (!vis[a]) if (!dfs(a, 2)) flag = false;
			if (vis[a] == 1) flag = false;
		}
		for (int i = 1; i <= n; i++) {
			if (vis[i]) continue;
			if (!dfs(i, 1)) flag = false;
		}
		for (int i = 1; i <= n; i++)
			if (!edges[i].size() && !vis[i]) flag = false;
		if (flag) printf("YES\n");
		else printf("NO\n");
	}


	return 0;
}
