#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

struct Node{
	Point king, nith;
	int step;
	Node() {}
	Node(Point a, Point b, int c) : king(a), nith(b), step(c) {}
	bool operator < (const Node &n) const {
		return abs(king.x - nith.x) + abs(king.y - nith.y) < abs(n.king.x - n.nith.x) + abs(n.king.y - n.nith.y);
	}
};

int T;
int n, m, k;
int sx, sy, ex, ey;
int dir[2][8][2] = {{{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}},
	{{1, 2}, {-1, 2}, {1, -2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}}};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}

map<Point, bool> vis[1005][1005];
int bfs() {
	priority_queue<Node> q;
	q.push(Node(Point(sx, sy), Point(ex, ey), 0));
	vis[sx][sy][Point(ex, ey)] = 1;
	int cnt = 0;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		cnt++;
		if (cnt == 1500000) break;
		for (int i = 0; i < 8; i++) {
			int nkx = dir[0][i][0] + cur.king.x;
			int nky = dir[0][i][1] + cur.king.y;
			if (!check(nkx, nky)) continue;
			for (int j = 0; j < 8; j++) {
				int nnx = dir[1][j][0] + cur.nith.x;
				int nny = dir[1][j][1] + cur.nith.y;
				if (!check(nnx, nny)) continue;
				if (vis[nkx][nky][Point(nnx, nny)]) continue;
				vis[nkx][nky][Point(nnx, nny)] = 1;
				if (nkx == nnx && nky == nny) return cur.step + 1;
				if (cur.step + 1 < k) q.push(Node(Point(nkx, nky), Point(nnx, nny), cur.step + 1));
			}
		}

	}
	return -1;
}

int main() {
	freopen("1005.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d %d %d", &n, &m, &k);
		scanf("%d %d", &sx, &sy);
		scanf("%d %d", &ex, &ey);
		int ans = bfs();
		printf("Case #%d:\n", cas++);
		if (ans == -1) printf("OH,NO!\n");
		else printf("%d\n", ans);
	}

	return 0;
}
	