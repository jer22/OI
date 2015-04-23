#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define p(i, j) (i - 1) * n + j

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

int n, m;
char g[20][20];
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
int dist[255][255];
Point hole[505][2];
bool vis[20][20];

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

void spfa(int x, int y) {
	memset(vis, 0, sizeof(vis));
	queue<Point> q;
	q.push(Point(x, y));
	int s = p(x, y);
	dist[s][s] = 0;
	vis[x][y] = 1;
	while (!q.empty()) {
		Point cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			if (g[nx][ny] == '#') continue;
			if (dist[s][p(cur.x, cur.y)] + 1 < dist[s][p(nx, ny)]) {
				dist[s][p(nx, ny)] = dist[s][p(cur.x, cur.y)] + 1;
				if (!vis[nx][ny]) {
					vis[nx][ny] = 1;
					q.push(Point(nx, ny));
				}
			}
		}
		vis[cur.x][cur.y] = 0;
	}
}

struct Node{
	int id, stat;
	Node() {}
	Node(int a, int b) : id(a), stat(b) {}
};

bool inq[20][32788];
int dis[20][32788];
void bfs() {
	queue<Node> q;
	memset(inq, 0, sizeof(inq));
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 0; i < m; i++) {
		q.push(Node(i, 1 << i));
		inq[i][1 << i] = 1;
		dis[i][1 << i] = 0;
	}
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		Point now = hole[cur.id][1];
		for (int i = 0; i < m; i++) {
			if (cur.stat & (1 << i)) continue;
			Point nex = hole[i][0];
			if (dis[cur.id][cur.stat] + dist[p(now.x, now.y)][p(nex.x, nex.y)] < dis[i][cur.stat | (1 << i)]) {
				dis[i][cur.stat | (1 << i)] = dis[cur.id][cur.stat] + dist[p(now.x, now.y)][p(nex.x, nex.y)];
				if (!inq[i][cur.stat | (1 << i)]) {
					inq[i][cur.stat | (1 << i)] = 1;
					q.push(Node(i, cur.stat | (1 << i)));
				}
			}
		}
		inq[cur.id][cur.stat] = 0;
	}
}

int main() {
	freopen("j.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		memset(dist, 0x3f, sizeof(dist));
		int a, b, c, d;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			hole[i][0] = Point(a, b);
			hole[i][1] = Point(c, d);
			spfa(c, d);
		}
		bfs();
		int ans = 0x3f3f3f3f;
		for (int i = 0; i < m; i++) {
			ans = min(ans, dis[i][(1 << m) - 1]);
		}
		if (ans == 0x3f3f3f3f) cout << -1 << endl;
		else cout << ans << endl;
	}
	return 0;
}
