#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

const int MAXN = 1005;

int n;
int map[MAXN][MAXN];
int dir[8][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool vis[MAXN][MAXN];

bool check(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= n);
}

struct Point{int x, y;};
void floodfill(int x, int y) {
	queue<Point> q;
	q.push((Point){x, y});
	// memset(vis, 0, sizeof(vis));
	vis[x][y] = 1;
	while (!q.empty()) {
		Point cur = q.front();
		q.pop();
		for (int i = 0; i < 8; i++) {
			int nx = cur.x + dir[i][0], ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			if (map[nx][ny] != map[x][y]) continue;
			if (!vis[nx][ny]) {
				vis[nx][ny] = 1;
				q.push((Point){nx, ny});
			}
		}
	}
}

int solve_top(bool op) {
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (vis[i][j]) continue;
			for (int k = 0; k < 8; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (!check(nx, ny)) continue;
				if (op) if (map[nx][ny] > map[i][j]) {
					floodfill(i, j);
					break;
				} else {}
				else if (map[nx][ny] < map[i][j]) {
					floodfill(i, j);
					break;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (!vis[i][j]) {
				floodfill(i, j),
				ans++;
			}
		}
	}
	return ans;
}

int main() {
	freopen("1102.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	int top_cnt = solve_top(1);
	int bot_cnt = solve_top(0);
	printf("%d %d\n", top_cnt, bot_cnt);

	return 0;
}
