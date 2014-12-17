#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Block{
	int x, y, cnt;
	Block(int a, int b, int c) : x(a), y(b), cnt(c) {}
	bool operator < (const Block & b) const {
		return cnt > b.cnt;
	}
};

struct Point{
	int x, y;
	Point(int a, int b) : x(a), y(b) {}
};

int n, m;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int arr[8][8];
int g[8][8];
int depth;
int vis[8][8];
int emp[8];
bool ended() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (g[i][j]) return false;
	return true;
}

int floodFill(int x, int y, int color) {
	int ans = 1;
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] == color && !vis[nx][ny]) {
			ans += floodFill(nx, ny, color);
		}
	}
	return ans;
}

void change() {
	memset(emp, 0, sizeof(emp));
	int t;
	for (int j = 0; j < m; j++) {
		for (int i = n - 1; i >= 0; i--) {
			if (g[i][j]) continue;
			int t = i;
			while (!g[t][j]) t--;
			if (t >= 0) {
				g[i][j] = g[t][j];
				g[t][j] = 0;
			}
		}
		for (t = n - 1; t >= 0; t--)
			if (g[t][j]) break;
		if (t < 0) emp[j] = 1;
	}
	for (int j = 0, flag = 0; j < m - flag; j++) {
		if (!emp[j]) continue;
		for (int i = n - 1; i >= 0; i--) {
			for (int k = j - flag + 1; k < m - flag; k++) {
				g[i][k - 1] = g[i][k];
			}
			g[i][m - flag - 1] = 0;
		}
		flag++;
	}
}

queue<Point> q;
void remv(int sx, int sy) {
	while (!q.empty()) q.pop();
	Point p = Point(sx, sy);
	q.push(p);
	int color = g[sx][sy];
	g[sx][sy] = 0;
	while (!q.empty()) {
		p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = p.x + dir[i][0];
			int ny = p.y + dir[i][1];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] == color) {
				g[nx][ny] = 0;
				q.push(Point(nx, ny));
			}
		}
	}
}

bool dfs(int step) {
	if (ended() && step == depth) return true;
	if (step > depth) return false;
	int map[8][8];
	memcpy(map, g, sizeof(g));
	memset(vis, 0, sizeof(vis));
	vector<Block> blocks;
	int color = 0;
	int done[5] = {0};
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!map[i][j] || vis[i][j]) continue;
			int num = floodFill(i, j, map[i][j]);
			blocks.push_back(Block(i, j, num));
			if (!done[map[i][j]]) {
				color++;
				done[map[i][j]] = 1;
			}
		}
	}
	if (color + step > depth) return false;
	sort(blocks.begin(), blocks.end());
	for (int i = 0; i < blocks.size(); i++) {
		memcpy(g, map, sizeof(map));
		remv(blocks[i].x, blocks[i].y);
		change();
		if (dfs(step + 1)) return true;
	}
	return false;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &arr[i][j]);
			}
		}
		for (depth = 0; depth < 2222; depth++) {
			memcpy(g, arr, sizeof(arr));
			if (dfs(0)) {
				printf("%d\n", depth);
				break;
			}
		}
	}
	return 0;
}
