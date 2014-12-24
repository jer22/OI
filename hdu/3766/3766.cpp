#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

int ex, ey;
struct Node{
	int x, y;
	int step;
	int dist;
	Node() {}
	Node(int a, int b, int c) : x(a), y(b), step(c) {
		dist = abs(ex - x) + abs(ey - y);
	}
	bool operator < (const Node &n) const {
		if (dist != n.dist) return dist > n.dist;
		return step > n.step;
	}
};
int dir[8][2] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
priority_queue<Node> q;
map<pair<int, int>, bool> vis;
int bfs() {
	vis.clear();
	while (!q.empty()) q.pop();
	q.push(Node(0, 0, 0));
	vis[make_pair(0, 0)] = 1;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		// cout << cur.x << ' ' << cur.y << endl;
		if (cur.x == ex && cur.y == ey) return cur.step;
		for (int i = 0; i < 8; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!vis[make_pair(nx, ny)]) {
				vis[make_pair(nx, ny)] = 1;
				q.push(Node(nx, ny, cur.step + 1));
			}
		}
	}
}

int toInt(char str[11]) {
	int res = 0;
	int base = 1;
	int len = strlen(str);
	for (int i = len - 1; i >= 0; i--) {
		res += base * (str[i] - '0');
		base *= 10;
	}
	return res;
}

int main() {
	freopen("3766.in", "r", stdin);
	freopen("3766.out", "w", stdout);
	char str[11];
	while (~scanf("%s", str)) {
		if (str[0] == 'E') break;
		ex = toInt(str);
		scanf("%d", &ey);
		int ans = bfs();
	}

	return 0;
}
