#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

int n, m, stp;
char map[55][55];
bool ans[55][55];
int move[1005];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

struct Node{
	int x, y, step;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), step(c) {}
};

bool vis[55][55][1005];

bool check(int x, int y, int step) {
	if (vis[x][y][step]) return false;
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	if (map[x][y] == 'X') return false;
	return true;
}

void BFS(int sx, int sy) {
	queue<Node> q;
	q.push(Node(sx, sy, 0));
	vis[sx][sy][0] = 1;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		int nx = cur.x, ny = cur.y;
		int dx = dir[move[cur.step]][0], dy = dir[move[cur.step]][1];
		while (check(nx + dx, ny + dy, cur.step + 1)) {
			nx += dx, ny += dy;
			// cout << nx << ' ' << ny << endl;
			if (cur.step + 1 == stp) {
				ans[nx][ny] = 1;
			} else {
				vis[nx][ny][cur.step + 1] = 1;
				q.push(Node(nx, ny, cur.step + 1));
			}
		}
	}

}

int main() {
	freopen("1026.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", map[i]);
	scanf("%d", &stp);
	char op[10];
	for (int i = 0; i < stp; i++) {
		scanf("%s", op);
		switch (op[0]) {
			case 'N' : move[i] = 1; break;
			case 'S' : move[i] = 0; break;
			case 'W' : move[i] = 3; break;
			case 'E' : move[i] = 2; break;
		}
	}
	int x, y;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (flag) break;
		for (int j = 0; j < m; j++) {
			if (map[i][j] == '*') {
				map[i][j] = '.';
				x = i, y = j;
				flag = true;
				break;
			}
		}
	}
	BFS(x, y);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (ans[i][j]) cout << '*';
			else cout << map[i][j];
		}
		cout << endl;
	}

	return 0;
}
