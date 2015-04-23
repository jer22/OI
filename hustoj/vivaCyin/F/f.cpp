#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define p(i, j) (i - 1) * m + j
#define getx(i) (i - 1) / m + 1
#define gety(i) (i - 1) % m + 1

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

int T, n, m;
char g[45][45];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int dist[45][45][45][45];
bool vis[45][45];

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

void spfa(int x, int y) {
	queue<Point> q;
	memset(vis, 0, sizeof(vis));
	dist[x][y][x][y] = 0;
	vis[x][y] = 1;
	q.push(Point(x, y));
	while (!q.empty()) {
		Point cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			int v = 0;
			if (g[cur.x][cur.y] != g[nx][ny]) v = 1;
			if (dist[x][y][nx][ny] > dist[x][y][cur.x][cur.y] + v) {
				dist[x][y][nx][ny] = dist[x][y][cur.x][cur.y] + v;
				if (!vis[nx][ny]) {
					vis[nx][ny] = 1;
					q.push(Point(nx, ny));
				}
			}
		}
		vis[cur.x][cur.y] = 0;
	}
}

bool flag[45][45];
int main() {
	freopen("f.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		memset(dist, 0x3f, sizeof(dist));
		int ans = 0x3f3f3f3f;
		memset(flag, 0, sizeof(flag));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (flag[i][j]) continue;
				spfa(i, j);
				int tmp = 0;
				for (int k = 1; k <= n; k++) {
					for (int l = 1; l <= m; l++) {
						if (dist[i][j][k][l] == 0) {
							flag[k][l] = 1;
						}
						tmp = max(tmp, dist[i][j][k][l]);
					}
				}
				ans = min(ans, tmp);
			}
		}
		printf("%d\n", ans);
	}



	return 0;
}
