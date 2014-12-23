#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int x, y;
	int step;
	int dir;
	Node() {}
	Node (int a, int b, int c, int d) : x(a), y(b), step(c), dir(d) {}
};

int n, m;
int dir[4][2]={{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int map[55][55];
int ex, ey;
Node start;
int dist[55][55][4];

int spfa() {
	memset(dist, 0x3f, sizeof(dist));
	dist[start.x][start.y][start.dir] = 0;
	queue<Node> q;
	q.push(start);
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (cur.x == ex && cur.y == ey) return cur.step;
		if (cur.step + 1 < dist[cur.x][cur.y][(cur.dir + 1) % 4]) {
			dist[cur.x][cur.y][(cur.dir + 1) % 4] = cur.step + 1;
			q.push(Node(cur.x, cur.y, cur.step + 1, (cur.dir + 1) % 4));
		}
		if (cur.step + 1 < dist[cur.x][cur.y][(cur.dir + 3) % 4]) {
			dist[cur.x][cur.y][(cur.dir + 3) % 4] = cur.step + 1;
			q.push(Node(cur.x, cur.y, cur.step + 1, (cur.dir + 3) % 4));
		}
		for (int i = 1; i <= 3; i++) {
			int nx = cur.x + i * dir[cur.dir][0];
			int ny = cur.y + i * dir[cur.dir][1];
			if (map[nx][ny] == 1) break;
			if (nx > 0 && nx < n && ny > 0 && ny < m && cur.step + 1 < dist[nx][ny][cur.dir]) {
				dist[nx][ny][cur.dir] = cur.step + 1;
				q.push(Node(nx, ny, cur.step + 1, cur.dir));
			}
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		memset(map, 0, sizeof(map));
		int t;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &t);
				if (t) map[i + 1][j] = map[i][j + 1] = map[i + 1][j + 1] = map[i][j] = 1;
			}
		}
		char sdir[8];
		scanf("%d %d %d %d", &start.x, &start.y, &ex, &ey);
		scanf("%s", sdir);
		if (sdir[0] == 'e') start.dir = 0;
		if (sdir[0] == 's') start.dir = 1;
		if (sdir[0] == 'w') start.dir = 2;
		if (sdir[0] == 'n') start.dir = 3;
		start.step = 0;
		int ans = spfa();
		cout << ans << endl;
	}
	return 0;
}
