#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[105];
int mat[105];
bool vis[105];

bool dfs(int u) {
	for (int i = 0; i < edges[u].size(); i++) {
		int v = edges[u][i];
		if (!vis[v]) {
			vis[v] = 1;
			if (!mat[v] || dfs(mat[v])) {
				mat[v] = u;
				return true;
			}
		}
	}
	return false;
}

int match() {
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		if (dfs(i)) ans++;
	}
	return ans;
}

bool map[105][105];
int main() {
	freopen("1143.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		map[a][b] = 1;
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				map[i][j] |= map[i][k] & map[k][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j && map[i][j]) edges[i].push_back(j);

	printf("%d\n", n - match());
	return 0;
}
