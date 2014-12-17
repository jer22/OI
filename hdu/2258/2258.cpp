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
		if (cnt != b.cnt) return cnt > b.cnt;
		if (x != b.x) return x < b.x;
		return y < b.y;
	}
};

struct Point{
	int x, y;
	Point(int a, int b) : x(a), y(b) {}
};

int n, m;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};
int arr[22][22];
int vis[22][22];
int emp[22];
vector<Block> blocks;
int floodFill(int x, int y, int color) {
	int ans = 1;
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 0 && nx < n && ny >= 0 && ny < m && arr[nx][ny] == color && !vis[nx][ny]) {
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
			if (arr[i][j]) continue;
			int t = i;
			while (!arr[t][j]) t--;
			if (t >= 0) {
				arr[i][j] = arr[t][j];
				arr[t][j] = 0;
			}
		}
		for (t = n - 1; t >= 0; t--)
			if (arr[t][j]) break;
		if (t < 0) emp[j] = 1;
	}
	for (int j = 0, flag = 0; j < m - flag; j++) {
		if (!emp[j]) continue;
		for (int i = n - 1; i >= 0; i--) {
			for (int k = j - flag + 1; k < m - flag; k++) {
				arr[i][k - 1] = arr[i][k];
			}
			arr[i][m - flag - 1] = 0;
		}
		flag++;
	}
}

void remv(int sx, int sy) {
	queue<Point> q;
	Point p = Point(sx, sy);
	int done[22][22];
	memset(done, 0, sizeof(done));
	q.push(p);
	int color = arr[sx][sy];
	arr[sx][sy] = 0;
	while (!q.empty()) {
		p = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = p.x + dir[i][0];
			int ny = p.y + dir[i][1];
			if (nx >= 0 && nx < n && ny >= 0 && ny < m && arr[nx][ny] == color) {
				arr[nx][ny] = 0;
				q.push(Point(nx, ny));
			}
		}
	}
}

int solve() {
	int score = 0;
	while (true) {
		blocks.clear();
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (!arr[i][j] || vis[i][j]) continue;
				int num = floodFill(i, j, arr[i][j]);
				if (num > 1)
					blocks.push_back(Block(i, j, num));
			}
		}
		if (blocks.empty()) break;
		sort(blocks.begin(), blocks.end());
		remv(blocks[0].x, blocks[0].y);
		score += blocks[0].cnt * (blocks[0].cnt - 1);
		change();
	}
	return score;
}

int main() {
	freopen("2258.in", "r", stdin);
	while (~scanf("%d %d\n", &n, &m)) {
		char c;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				arr[i][j] = c - '0';
			}
			getchar();
		}
		int ans = solve();
		printf("%d\n", ans);
	}
	return 0;
}
