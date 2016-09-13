#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
char arr[105][105];
bool vis[105][105];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(int i, int j) {
	if (vis[i][j]) return false;
	if (arr[i][j] != '#') return false;
	return i >= 1 && i <= n && j >= 1 && j <= m;
}

void dfs(int i, int j) {
	vis[i][j] = 1;
	for (int k = 0; k < 4; k++) {
		int ni = i + dir[k][0];
		int nj = j + dir[k][1];
		if (!check(ni, nj)) continue;
		dfs(ni, nj);
	}
}

int main() {
	freopen("2952.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%s", arr[i] + 1);
		memset(vis, 0, sizeof(vis));
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (!vis[i][j] && (arr[i][j] == '#')) {
					dfs(i, j);
					ans++;
				}
			}
		}
		printf("%d\n", ans);
	}


	return 0;
}
