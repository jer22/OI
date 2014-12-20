#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>
#include <utility>

using namespace std;

struct Node{
	int x, y, step;
	int bombCnt;	// 拥有的炸弹个数
	long long walls; // 地图上的墙的状态，0表示破坏，1表示还在
	long long expls; // 地图上炸药的状态，0表示还在，1表示取走
	Node() {}
	Node(int a, int b, int c, int d, long long e, long long f)
		: x(a), y(b), bombCnt(c), step(d), expls(e), walls(f) {}
	// 优先队列
	bool operator < (const Node &n) const {
		return step > n.step;
	}
};

int n, m;
int ex, ey;
char maze[11][11];
int wall[11][11];
int bomb[11][11];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int walls, bombs;
Node start;

int bfs() {
	map<pair<long long, long long>, bool> vis[11][11];
	priority_queue<Node> q;
	q.push(start);
	vis[start.x][start.y][make_pair(start.walls, start.expls)] = 1;
	Node nex;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (cur.x == ex && cur.y == ey) return cur.step;
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (maze[nx][ny] == 'X' && (cur.walls & (1ll << wall[nx][ny]))) {
				if (!cur.bombCnt) continue;
				nex = Node(nx, ny, cur.bombCnt - 1, cur.step + 2, cur.expls, cur.walls ^ (1ll << wall[nx][ny]));
				vis[nx][ny][make_pair(nex.walls, nex.expls)] = 1;
				q.push(nex);
			} else if ((maze[nx][ny] >= '0' && maze[nx][ny] <= '9') && !(cur.expls & (1ll << bomb[nx][ny]))) {
				nex = Node(nx, ny, cur.bombCnt + maze[nx][ny] - '0', cur.step + 1, cur.expls | (1ll << bomb[nx][ny]), cur.walls);
				vis[nx][ny][make_pair(nex.walls, nex.expls)] = 1;
				q.push(nex);
			} else {
				if (!vis[nx][ny][make_pair(cur.walls, cur.expls)]) {
					vis[nx][ny][make_pair(cur.walls, cur.expls)] = 1;
					q.push(Node(nx, ny, cur.bombCnt, cur.step + 1, cur.expls, cur.walls));
				}
			}
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		for (int i = 0; i < n; i++)
			scanf("%s", maze[i]);
		memset(wall, -1, sizeof(wall));
		memset(bomb, -1, sizeof(bomb));
		walls = bombs = 0;
		start.step = start.expls = start.bombCnt = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (maze[i][j] == 'S') {
					start.x = i;
					start.y = j;
				} else if (maze[i][j] == 'D') {
					ex = i;
					ey = j;
				} else if (maze[i][j] == 'X') {
					wall[i][j] = walls++;
				} else if (maze[i][j] >= '0' && maze[i][j] <= '9') {
					bomb[i][j] = bombs++;
				}
			}
		}
		start.walls = (1ll << walls) - 1;
		int ans = bfs();
		cout << ans << endl;
	}
	return 0;
}
