#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
}s1, s2, e1, e2;

struct Node{
	Point a, b;
	double mindist;
	Node() {}
	Node(Point c, Point d, int e)
		: a(c), b(d), mindist(e) {}
	bool operator < (const Node &n) const {
		if (fabs(mindist - n.mindist) > eps)
			return mindist - n.mindist < -eps;
		int d = abs(s1.x - a.x) + abs(s1.y - a.y) + abs(s2.x - b.x) + abs(s2.y - b.y);
		int nd = abs(s1.x - n.a.x) + abs(s1.y - n.a.y) + abs(s2.x - n.b.x) + abs(s2.y - n.b.y);
		return d > nd;
	}
};

bool operator == (Point a, Point b) {
	return a.x == b.x && a.y == b.y;
}

double getdist(Point a, Point b) {
	double dx = double(a.x) - double(b.x);
	double dy = double(a.y) - double(b.y);
	return dx * dx + dy * dy;
}

int n;
char g[35][35];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool vis[35][35][35][35];

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

double bfs() {
	priority_queue<Node> q;
	q.push(Node(s1, s2, getdist(s1, s2)));
	vis[s1.x][s1.y][s2.x][s2.y] = 1;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		int nx1, ny1, nx2, ny2;
		for (int i = 0; i < 4; i++) {
			if (cur.a == e1) {
				nx1 = cur.a.x, ny1 = cur.a.y;
			} else {
				nx1 = cur.a.x + dir[i][0];
				ny1 = cur.a.y + dir[i][1];
				if (!check(nx1, ny1)) continue;
				if (g[nx1][ny1] == '*') continue;
				if (g[nx1][ny1] == 'h' || g[nx1][ny1] == 's') continue;
			}
			for (int j = 0; j < 4; j++) {
				if (cur.b == e2) {
					nx2 = cur.b.x, ny2 = cur.b.y;
				} else {
					nx2 = cur.b.x + dir[j][0];
					ny2 = cur.b.y + dir[j][1];
					if (!check(nx2, ny2)) continue;
					if (g[nx2][ny2] == '*') continue;
					if (g[nx2][ny2] == 'H' || g[nx2][ny2] == 'S') continue;
				}
				if (vis[nx1][ny1][nx2][ny2]) continue;
				Point n1 = Point(nx1, ny1);
				Point n2 = Point(nx2, ny2);
				if (n1 == e1 && n2 == e2) return cur.mindist;
				vis[nx1][ny1][nx2][ny2] = 1;
				q.push(Node(n1, n2, min(cur.mindist, getdist(n1, n2))));
			}
		}
	}

}

int main() {
	freopen("2195.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", g[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (g[i][j] == 'H') s1 = Point(i, j);
			if (g[i][j] == 'S') e1 = Point(i, j);
			if (g[i][j] == 'h') s2 = Point(i, j);
			if (g[i][j] == 's') e2 = Point(i, j);
		}
	}
	double ans = min(bfs(), getdist(e1, e2));
	ans = sqrt(ans);
	printf("%.2lf\n", ans);
	return 0;
}
