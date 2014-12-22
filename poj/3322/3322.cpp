#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

#define INF 0x3f

using namespace std;

struct Node{
	int x1, y1, x2, y2;
	int step;
	Node() {}
	Node(int a, int b, int c, int d, int e)
		: x1(a), y1(b), x2(c), y2(d), step(e) {}
}cur;

int n, m;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
char map[511][511];
int vis[511][511][3];
int sx1, sy1, sx2, sy2;
int nx1, ny1, nx2, ny2;
Node start;

bool check() {
	if (nx1 < 0 || nx1 >= n || nx2 < 0 || nx2 >= n
		|| ny1 < 0 || ny1 >= m || ny2 < 0 || ny2 >= m
		|| map[nx1][ny1] == '#' || map[nx2][ny2] == '#') return false;
	if (nx1 == nx2 && ny1 == ny2 && map[nx1][ny1] == 'E') return false;
	return true;
}

queue<Node> q;
void solve(int dir) {
	if (check()) {
		if (!vis[nx1][ny1][dir]) {
			vis[nx1][ny1][dir] = 1;
			q.push(Node(nx1, ny1, nx2, ny2, cur.step + 1));
		}
	}
}

int spfa() {
	while (!q.empty()) q.pop();
	memset(vis, 0, sizeof(vis));
	if (sx1 == sx2 && sy1 == sy2) vis[sx1][sy1][2] = 1;
	else if (sx1 + 1 == sx2) vis[sx1][sy1][1] = 1;
	else if (sy1 + 1 == sy2) vis[sx1][sy1][0] = 1;
	
	q.push(start);
	while (!q.empty()) {
		cur = q.front();
		if (map[cur.x1][cur.y1] == 'O' && map[cur.x2][cur.y2] == 'O') return cur.step;
		q.pop();
		if (cur.x1 + 1 == cur.x2) {
			ny1 = ny2 = cur.y1;
			nx1 = nx2 = cur.x1 - 1;
			solve(2);
			nx1 = nx2 = cur.x2 + 1;
			solve(2);
			nx1 = cur.x1, nx2 = cur.x2;
			ny1 = ny2 = cur.y1 - 1;
			solve(1);
			ny1 = ny2 = cur.y1 + 1;
			solve(1);
		} else if (cur.y1 + 1 == cur.y2) {
			nx1 = nx2 = cur.x1;
			ny1 = ny2 = cur.y1 - 1;
			solve(2);
			ny1 = ny2 = cur.y2 + 1;
			solve(2);
			ny1 = cur.y1, ny2 = cur.y2;
			nx1 = nx2 = cur.x1 - 1;
			solve(0);
			nx1 = nx2 = cur.x1 + 1;
			solve(0);
		} else {
			for (int i = 0; i < 4; i++) {
				nx1 = cur.x1 + dir[i][0] + dir[i][0];
				ny1 = cur.y1 + dir[i][1] + dir[i][1];
				nx2 = cur.x2 + dir[i][0];
				ny2 = cur.y2 + dir[i][1];
				if (nx1 > nx2) swap(nx1, nx2);
				if (ny1 > ny2) swap(ny1, ny2);
				solve(i & 1);
			}
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		sx1 = sy1 = sx2 = sy2 = -1;
		for (int i = 0; i < n; i++)
			scanf("%s", map[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (map[i][j] == 'X') {
					if (sx1 == -1) sx1 = i, sy1 = j;
					else sx2 = i, sy2 = j;
				}
			}
		}
		if (sx2 == -1) sx2 = sx1, sy2 = sy1;
		start = Node(sx1, sy1, sx2, sy2, 0);
		int ans = spfa();
		if (ans == -1) printf("Impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
