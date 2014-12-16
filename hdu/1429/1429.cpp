#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int x;
	int y;
	int step;
	int key;
	Node() {}
	Node(int a, int b, int s, int k) : x(a), y(b), step(s), key(k) {}
};

int n, m, t;
int arr[25][25];
int door[25][25];
int key[25][25];
int Go[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int sx, sy;
int ex, ey;
int vis[25][25][1049];

bool canGo(int x, int y, int k) {
	if (x >= 0 && x < n && y >= 0 && y < m && !arr[x][y]) {
		if (vis[x][y][k]) return false;
		if ((k & door[x][y]) == door[x][y]) return true;
	}
	return false;
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	queue<Node> q;
	Node s = Node(sx, sy, 0, 0);
	q.push(s);
	vis[sx][sy][0] = 1;
	while (!q.empty()) {
		Node e = q.front();
		q.pop();
		if (e.x == ex && e.y == ey) return e.step;
		for (int i = 0; i < 4; i++) {
			int nx = e.x + Go[i][0];
			int ny = e.y + Go[i][1];
			if (canGo(nx, ny, e.key)) {
				Node nex = Node(nx, ny, e.step + 1, e.key | key[nx][ny]);
				vis[nx][ny][nex.key] = 1;
				q.push(nex);
			}
		}
	}
	return 0;
}

int main() {
	freopen("1429.in", "r", stdin);
	while (~scanf("%d %d %d\n", &n, &m, &t)) {
		memset(arr, 0, sizeof(arr));
		memset(door, 0, sizeof(door));
		memset(key, 0, sizeof(key));
		char c;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				if (c == '*') arr[i][j] = 1;
				else if (c == '@') sx = i, sy = j;
				else if (c == '^') ex = i, ey = j;
				else if (c >= 'a' && c <= 'z') key[i][j] = 1 << (c - 'a');
				else if (c >= 'A' && c <= 'Z') door[i][j] = 1 << (c - 'A');
			}
			getchar();
		}
		int ans = bfs();
		if (ans < t && ans) printf("%d\n", ans);
		else printf("-1\n");
	}
	return 0;
}
