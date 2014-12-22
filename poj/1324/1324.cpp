#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int x, y, step, stat;
	Node() {}
	Node(int a, int b, int c, int d) : x(a), y(b), step(c), stat(d) {}
	bool operator < (const Node &n) const {
		int dist = x + y - 2;
		int ndist = n.x + n.y - 2;
		return step + dist > n.step + ndist;
	}
};

int n, m, l, k;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int map[22][22];
bool vis[22][22][16388];
Node start;
int direction[11];
bool check(int x, int y, Node cur) {
	if (x < 1 || x > n || y < 1 || y > m || map[x][y] == 1) return false;
	for (int i = l - 1; i >= 1; i--) {
		direction[i] = cur.stat & 3;
		cur.stat >>= 2;
	}
	for (int i = 1; i < l; i++) {
		cur.x += dir[direction[i]][0];
		cur.y += dir[direction[i]][1];
		if (cur.x == x && cur.y == y) return false;
	}
	return true;
}

int bfs() {
	if (start.x == 1 && start.y == 1) return 0;
	memset(vis, 0, sizeof(vis));
	priority_queue<Node> q;
	q.push(start);
	vis[start.x][start.y][start.stat] = 1;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny, cur)) continue;
			int pos = (i + 2) % 4;
			int stat = (cur.stat >> 2) + (pos << ((l << 1) - 4));
			if (!vis[nx][ny][stat]) {
				vis[nx][ny][stat] = 1;
				if (nx == 1 && ny == 1) return cur.step + 1;
				q.push(Node(nx, ny, cur.step + 1, stat));
			}
		}
	}
	return -1;
}

int main() {
	int cas = 1;
	while (~scanf("%d %d %d", &n, &m, &l) && n && m && l) {
		memset(map, 0, sizeof(map));
		int x, y;
		scanf("%d %d", &x, &y);
		start = Node(x, y, 0, 0);
		int stat = 0;
		int prex = x, prey = y;
		int pos;
		for (int i = 1; i < l; i++) {
			scanf("%d %d", &x, &y);
			if (x == prex - 1) pos = 0;
			if (x == prex + 1) pos = 2;
			if (y == prey - 1) pos = 3;
			if (y == prey + 1) pos = 1;
			prex = x, prey = y;
			stat <<= 2;
			stat |= pos;
		}
		start.stat = stat;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			scanf("%d %d", &x, &y);
			map[x][y] = 1;
		}
		int ans = bfs();
		printf("Case %d: %d\n", cas++, ans);
	}
	return 0;
}
