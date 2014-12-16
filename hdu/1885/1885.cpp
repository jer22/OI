#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node{
	int x;
	int y;
	int step;
	int key;
	Node() {}
	Node(int a, int b, int s, int k) : x(a), y(b), step(s), key(k) {}
};

int n, m;
int arr[111][111];
int door[111][111];
int key[111][111];
int Go[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int sx, sy;
int escape[111][111];
int vis[111][111][20];
map<char, int> K;
bool canGo(int x, int y, int k) {
	if (x >= 0 && x < n && y >= 0 && y < m && !arr[x][y]) {
		if (vis[x][y][k]) return false;
		if ((k & door[x][y]) == door[x][y]) return true;
	}
	return false;
}

int bfs() {
	int ans = 0x3f3f3f3f;
	memset(vis, 0, sizeof(vis));
	queue<Node> q;
	Node s = Node(sx, sy, 0, 0);
	q.push(s);
	vis[sx][sy][0] = 1;
	while (!q.empty()) {
		Node e = q.front();
		q.pop();
		
		if (escape[e.x][e.y]) ans = min(ans, e.step);

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
	return ans;
}

int main() {
	K['b'] = K['B'] = 0;
	K['y'] = K['Y'] = 1;
	K['r'] = K['R'] = 2;
	K['g'] = K['G'] = 3;
	while (~scanf("%d %d\n", &n, &m) && n && m) {
		memset(arr, 0, sizeof(arr));
		memset(door, 0, sizeof(door));
		memset(key, 0, sizeof(key));
		memset(escape, 0, sizeof(escape));
		char c;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%c", &c);
				if (c == '#') arr[i][j] = 1;
				else if (c == '*') sx = i, sy = j;
				else if (c == 'X') escape[i][j] = 1;
				else if (c >= 'a' && c <= 'z') key[i][j] = 1 << K[c];
				else if (c >= 'A' && c <= 'Z') door[i][j] = 1 << K[c];
			}
			getchar();
		}
		int ans = bfs();
		if (ans != 0x3f3f3f3f) printf("Escape possible in %d steps.\n", ans);
		else printf("The poor student is trapped!\n");
	}
	return 0;
}
