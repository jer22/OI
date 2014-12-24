#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Node{
	int x, y;
	int step;
	int pos;
	char top, bottom, front, back, left, right;
	long long hash;
	Node() {
		x = y = -1;
		step = pos = 0;
		top = 'r';
		bottom = 'c';
		front = 'm';
		back = 'g';
		left = 'y';
		right = 'b';
		hash = getHash();
	}
	long long getHash() {
		hash = 0;
		hash = hash * 13 + right;
		hash = hash * 13 + left;
		hash = hash * 13 + back;
		hash = hash * 13 + front;
		hash = hash * 13 + bottom;
		hash = hash * 13 + top;
		return hash;
	}
	void rotate(int dir) {
		char t;
		if (dir == 0) {
			t = top; top = back; back = bottom; bottom = front; front = t;
		} else if (dir == 1) {
			t = top; top = left; left = bottom; bottom = right; right = t;
		} else if (dir == 2) {
			t = top; top = front; front = bottom; bottom = back; back = t;
		} else if (dir == 3) {
			t = top; top = right; right = bottom; bottom = left; left = t;
		}
		hash = getHash();
	}
}s, cur, nex;

int n, m;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
char surface[33][33];
char seq[7];

bool check(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m && (surface[x][y] != 'k'));
}

int bfs() {
	map<long long, bool> vis[33][33][7];
	vis[s.x][s.y][s.pos][s.hash] = 1;
	queue<Node> q;
	q.push(s);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur.pos == 6) return cur.step;
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			nex = cur;
			nex.step++;
			nex.rotate(i);
			if (surface[nx][ny] != 'w') {
				if ((surface[nx][ny] == nex.top) && (seq[nex.pos] == nex.top))
					nex.pos++;
				else continue;
			}
			if (!vis[nx][ny][nex.pos][nex.hash]) {
				vis[nx][ny][nex.pos][nex.hash] = 1;
				nex.x = nx;
				nex.y = ny;
				q.push(nex);
			}
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d", &m, &n) && n && m) {
		s = Node();
		for (int i = 0; i < n; i++)
			scanf("%s", surface[i]);
		scanf("%s", seq);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (surface[i][j] == '#') {
					s.x = i;
					s.y = j;
					surface[i][j] = 'w';
				}
			}
		}
		int ans = bfs();
		if (ans == -1) printf("unreachable\n");
		else printf("%d\n", ans);
	}
	return 0;
}
