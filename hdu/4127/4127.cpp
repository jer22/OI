#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int map[11][11];
int vis[11][11];
void floodFill(int x, int y, int color) {
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 0 && nx < n && ny >= 0 && ny < n && vis[nx][ny] != 1) {
			if (map[nx][ny] == color)
				floodFill(nx, ny, color);
			else vis[nx][ny] = 2;
		}
	}
}

bool flag[6];
int H() {
	memset(flag, 0, sizeof(flag));
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (vis[i][j] == 1 || flag[map[i][j]]) continue;
			cnt++;
			flag[map[i][j]] = 1;
		}
	}
	return cnt;
}

bool effect(int color) {
	bool flag = false;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] != color || vis[i][j] != 2) continue;
			flag = true;
			floodFill(i, j, map[i][j]);
		}
	}
	return flag;
}

int depth;
bool dfs(int step) {
	if (step == depth) return !H();
	if (step + H() > depth) return false;
	int g[11][11];
	memcpy(g, vis, sizeof(g));
	for (int i = 0; i < 6; i++) {
		if (!effect(i)) continue;
		if (dfs(step + 1)) return true;
		memcpy(vis, g, sizeof(vis));
	}
	return false;
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(map, 0, sizeof(map));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &map[i][j]);
		floodFill(0, 0, map[0][0]);
		for (depth = H(); depth < 1111111; depth++)
			if (dfs(0)) break;
		cout << depth << endl;
	}
	return 0;
}
