#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

#define P(i, j) ((i) * 5 + (j))

using namespace std;

char g[6][6];
map<int, bool> vis;
int ans = 0;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(int x, int y) {
	return (x >= 0 && x < 5 && y >= 0 && y < 5);
}

void dfs(int step, int stat, int cnt) {
	if (step == 7) {
		ans++;
		return;
	}
	for (int i = 0; i < 25; i++) {
		if (stat & (1 << i)) {
			int x = i / 5, y = i % 5;
			for (int k = 0; k < 4; k++) {
				int nx = x + dir[k][0], ny = y + dir[k][1];
				if (!check(nx, ny)) continue;
				int v = cnt + (g[nx][ny] == 'H');
				int nex_stat = stat | (1 << P(nx, ny));
				if (v > 3) continue;
				if (vis[nex_stat]) continue;
				vis[nex_stat] = 1;
				dfs(step + 1, nex_stat, v);
			}
		}
	}

}

int main() {
	freopen("1675.in", "r", stdin);
	for (int i = 0; i < 5; i++)
		scanf("%s", g[i]);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!vis[1 << P(i, j)]) {
				vis[1 << P(i, j)] = 1;
				dfs(1, 1 << P(i, j), g[i][j] == 'H');
			}
		}
	}
	// vis[1 << 0] = 1;
	// dfs(1, 1 << 0, 1);
	printf("%d\n", ans);

	return 0;
}
