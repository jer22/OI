#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Node{
	int x, y, z, step;
	Node() {}
	Node(int a, int b, int c, int d) : x(a), y(b), z(c), step(d) {}
};

int T;
int n, m, tim;
int arr[12][12][2];
int door[12][12][2];
int Go[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int ex, ey, ez;
int vis[12][12][2];

int canGo(int x, int y, int z) {

	if (x < 0 || x >= n || y < 0 || y >= m) return -1;
	int nz = z;
	if (door[x][y][z]) nz ^= 1;
	if (arr[x][y][nz] || vis[x][y][nz] || door[x][y][nz]) return -1;
	return nz;
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	Node e = Node(0, 0, 0, 0);
	queue<Node> q;
	vis[0][0][0] = 1;
	q.push(e);
	while (!q.empty()) {
		e = q.front(); 
		q.pop();
		if (e.x == ex && e.y == ey && e.z == ez) return e.step;
		for (int i = 0; i < 4; i++) {
			int nx = e.x + Go[i][0];
			int ny = e.y + Go[i][1];
			int nz = canGo(nx, ny, e.z);
			if (nz != -1) {
				Node nex = Node(nx, ny, nz, e.step + 1);
				vis[nx][ny][nz] = 1;
				q.push(nex);
			}
		}
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(arr, 0, sizeof(arr));
		memset(door, 0, sizeof(door));
		scanf("%d %d %d\n", &n, &m, &tim);
		char c;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				if (c == '*') arr[i][j][0] = 1;
				else if (c == 'P') ex = i, ey = j, ez = 0;
				else if (c == '#') door[i][j][0] = 1;
			}
			getchar();
		}
		getchar();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				if (c == '*') arr[i][j][1] = 1;
				else if (c == 'P') ex = i, ey = j, ez = 1;
				else if (c == '#') door[i][j][1] = 1;
			}
			getchar();
		}
		int ans = bfs();
		if (ans && ans <= tim) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
