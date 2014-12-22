#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int bx, by, px, py;
	int step;
	Node() {step = 0;}
	Node(int a, int b, int c, int d, int e) : bx(a), by(b), px(c), py(d), step(e) {}
};

int T;
int n, m;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int map[11][11];
int preach[11][11];
Node start = Node();

bool canGo(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m && (map[x][y] != 1));
}

void dfs(int bx, int by, int px, int py) {
	preach[px][py] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = px + dir[i][0];
		int ny = py + dir[i][1];
		if ((nx != bx || ny != by) && canGo(nx, ny) && !preach[nx][ny]) dfs(bx, by, nx, ny);
	}
}

bool vis[11][11][4];
int bfs() {
	queue<Node> q;
	memset(vis, 0, sizeof(vis));
	q.push(start);
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (map[cur.bx][cur.by] == 3) return cur.step;
		memset(preach, 0, sizeof(preach));
		dfs(cur.bx, cur.by, cur.px, cur.py);
		for (int i = 0; i < 4; i++) {
			int px = cur.bx + dir[(i + 2) % 4][0];
			int py = cur.by + dir[(i + 2) % 4][1];
			if (canGo(px, py) && preach[px][py]) {
				int nx = cur.bx + dir[i][0];
				int ny = cur.by + dir[i][1];
				if (canGo(nx, ny) && !vis[nx][ny][i]) {
					vis[nx][ny][i] = 1;
					q.push(Node(nx, ny, cur.bx, cur.by, cur.step + 1));
				}
			}
		}
	}
	return -1;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(map, 0, sizeof(map));
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &map[i][j]);
				if (map[i][j] == 2) {
					start.bx = i;
					start.by = j;
				}
				if (map[i][j] == 4) {
					start.px = i;
					start.py = j;
				}
			}
		}
		int ans = bfs();
		printf("%d\n", ans);
	}

	return 0;
}
