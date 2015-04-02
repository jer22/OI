#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int n, m, T;
char map[105][105];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int sx, sy, ex, ey;

struct Node{
	int x, y, step;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), step(c) {}
};

bool check(int x, int y, int step) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	if (map[x][y] == '*') return false;
	if (abs(ex - x) + abs(ey - y) > T - step) return false;
	return true;
}

int tot[105][105][18];
bool vis[105][105][18];
int bfs() {
	queue<Node> q;
	tot[sx][sy][0] = 1;
	vis[sx][sy][0] = 1;
	q.push(Node(sx, sy, 0));
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (check(nx, ny, cur.step + 1)) {
				tot[nx][ny][cur.step + 1] += tot[cur.x][cur.y][cur.step];
				if (cur.step + 1 < T && !vis[nx][ny][cur.step + 1]) {
					vis[nx][ny][cur.step + 1] = 1;
					q.push(Node(nx, ny, cur.step + 1));
				}
			}
		}
		vis[cur.x][cur.y][cur.step] = 0;
	}
	return tot[ex][ey][T];
}

int main() {
	scanf("%d %d %d", &n, &m, &T);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
	sx--, sy--, ex--, ey--;
	int res = bfs();
	printf("%d\n", res);
	return 0;
}
