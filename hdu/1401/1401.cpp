#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

struct Point{
	int x, y;
	bool operator < (const Point & p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

struct Node{
	Point pos[4];
	int step;
}s, e, cur, nex;

map<int, int> vis;
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int getHash(Point *pos) {
	sort(pos, pos + 4);
	int hash = 0;
	for (int i = 0; i < 4; i++) {
		hash <<= 3;
		hash |= pos[i].x;
		hash <<= 3;
		hash |= pos[i].y;
	}
	return hash;
}

bool check(int x, int y) {
	return x >= 0 && x < 8 && y >= 0 && y < 8;
}

bool bfs(Node u, int flag) {
	u.step = 0;
	queue<Node> q;
	if (flag == 2) {
		if (vis[getHash(u.pos)])
			return true;
	}
	vis[getHash(u.pos)] = flag;
	q.push(u);
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur.step >= 4) continue;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				nex = cur;
				nex.step++;
				nex.pos[j].x += dir[i][0];
				nex.pos[j].y += dir[i][1];
				if (!check(nex.pos[j].x, nex.pos[j].y)) continue;
				int k;
				for (k = 0; k < 4; k++)
					if (k != j && nex.pos[k].x == nex.pos[j].x && nex.pos[k].y == nex.pos[j].y)
						break;
				if (k == 4) {
					int hash = getHash(nex.pos);
					if (!vis[hash]) {
						vis[hash] = flag;
						q.push(nex);
					} else if (flag == 2 && vis[hash] == 1)
						return true;
				} else {
					nex.pos[j].x += dir[i][0];
					nex.pos[j].y += dir[i][1];
					if (!check(nex.pos[j].x, nex.pos[j].y)) continue;
					for (k = 0; k < 4; k++)
						if (k != j && nex.pos[k].x == nex.pos[j].x && nex.pos[k].y == nex.pos[j].y)
							break;
					if (k != 4) continue;
					int hash = getHash(nex.pos);
					if (!vis[hash]) {
						vis[hash] = flag;
						q.push(nex);
					} else if (flag == 2 && vis[hash] == 1)
						return true;
				}
			}
		}
	}
	return false;
}

int main() {
	while (~scanf("%d %d", &s.pos[0].x, &s.pos[0].y)) {
		vis.clear();
		s.pos[0].x--;
		s.pos[0].y--;
		for (int i = 1; i < 4; i++) {
			scanf("%d %d", &s.pos[i].x, &s.pos[i].y);
			s.pos[i].x--;
			s.pos[i].y--;
		}
		for (int i = 0; i < 4; i++) {
			scanf("%d %d", &e.pos[i].x, &e.pos[i].y);
			e.pos[i].x--;
			e.pos[i].y--;
		}
		bfs(s, 1);
		bool ans = bfs(e, 2);
		if (ans) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
