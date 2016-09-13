#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
char arr[25][25];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool vis[25][25];

bool check(int i, int j) {
	return (i >= 1) && (i <= n) && (j >= 1) && (j <= m) && !vis[i][j] && (arr[i][j] != '#');
}

int dfs(int i, int j) {
	int ans = 1;
	vis[i][j] = 1;
	for (int k = 0; k < 4; k++) {
		int ni = i + dir[k][0];
		int nj = j + dir[k][1];
		if (!check(ni, nj)) continue;
		ans += dfs(ni, nj);
	}
	return ans;
}

int main() {
	freopen("1312.in", "r", stdin);
	int sx, sy;
	while (~scanf("%d %d\n", &m, &n)) {
		if (!n && !m) break;
		for (int i = 1; i <= n; i++) {
			scanf("%s", arr[i] + 1);
			for (int j = 1; j <= m; j++)
				if (arr[i][j] == '@') sx = i, sy = j;
		}
		memset(vis, 0, sizeof(vis));
		printf("%d\n", dfs(sx, sy));
	}



	return 0;
}
