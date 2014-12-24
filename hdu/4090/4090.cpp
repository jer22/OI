#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m, k;
int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
int g[11][11];
int ans = 0;

int best() {
	int cnt[7];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cnt[g[i][j]]++;
	int res = 0;
	for (int i = 1; i <= k; i++)
		res += cnt[i] * cnt[i];
	return res;
}

int floodFill(int x, int y, int color, bool vis[11][11]) {
	int res = 1;
	vis[x][y] = 1;
	g[x][y] = 0;
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] == color && !vis[nx][ny]) {
			res += floodFill(nx, ny, color, vis);
		}
	}
	return res;
}

bool flag[10];
void change() {
	int t = n;
	memset(flag, 0, sizeof(flag));
	for(int i = 1; i <= m; i++) {
		t = n;
		for(int j = n; j >= 1; j--) {
			g[t][i] = g[j][i];
			if(j < t)
				g[j][i] = 0;
			if(g[t][i]) {
				t--;
				flag[i] = true;
			}
		}
	}
	t = 1;
	for(int i = 1; i <= m; i++) {
		if(!flag[i]) continue;
		if(i > t) {
			for(int j = 1; j <= n; j++) {
				g[j][t] = g[j][i];
				g[j][i] = 0;
			}
		}
		t++;
	}
}

void dfs(int now) {
	if (now + best() <= ans) return;
	int map[11][11];
	bool vis[11][11];
	ans = max(ans, now);
	memcpy(map, g, sizeof(map));
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			memcpy(g, map, sizeof(g));
			if (g[i][j] && !vis[i][j]) {
				int cnt = floodFill(i, j, g[i][j], vis);
				if (cnt < 3) continue;
				change();
				dfs(now + cnt * cnt);
			}
		}
	}
}

int main() {
	while (~scanf("%d %d %d", &n, &m, &k)) {
		memset(g, 0, sizeof(g));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &g[i][j]);
		ans = 0;
		dfs(0);
		cout << ans << endl;
	}
	return 0;
}
