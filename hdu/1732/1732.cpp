#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node{
	int x, y;
	int step;
	char map[9][9];
	int box[3][2];
	Node() {
		x = y = step = 0;
		memset(map, 0, sizeof(map));
		memset(box, 0, sizeof(box));
	}
}s, cur, nex;

int n, m;
int dir[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
bool vis[9][9][9][9][9][9][9][9];

bool done() {
	return s.map[cur.box[0][0]][cur.box[0][1]] == '@'
		&& s.map[cur.box[1][0]][cur.box[1][1]] == '@'
		&& s.map[cur.box[2][0]][cur.box[2][1]] == '@';
}

bool check(int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m && s.map[x][y] != '#');
}

int bfs() {
	memset(vis, 0, sizeof(vis));
	queue<Node> q;
	q.push(s);
	vis[s.x][s.y][s.box[0][0]][s.box[0][1]][s.box[1][0]][s.box[1][1]][s.box[2][0]][s.box[2][1]] = 1;
	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (done()) return cur.step;
		for (int i = 0; i < 4; i++) {
			nex = cur;
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (!check(nx, ny)) continue;
			if (vis[nx][ny][nex.box[0][0]][nex.box[0][1]][nex.box[1][0]][nex.box[1][1]][nex.box[2][0]][nex.box[2][1]])
				continue;
			if (nex.map[nx][ny] == '*') {
				int bx = nx + dir[i][0];
				int by = ny + dir[i][1];
				if ((!check(bx, by)) || nex.map[bx][by] == '*') continue;
				int box;
				for (box = 0; box < 3; box++)
					if (nex.box[box][0] == nx && nex.box[box][1] == ny)
						break;
				nex.map[bx][by] = '*';
				nex.map[nx][ny] = nex.map[cur.x][cur.y] = '.';
				if (s.map[cur.x][cur.y] == '@') nex.map[cur.x][cur.y] = '@';
				if (s.map[nx][ny] == '@') nex.map[nx][ny] = '@';
				nex.box[box][0] = bx;
				nex.box[box][1] = by;
				if ((vis[nx][ny][nex.box[0][0]][nex.box[0][1]][nex.box[1][0]][nex.box[1][1]][nex.box[2][0]][nex.box[2][1]]))
					continue;
			}
			nex.step++;
			nex.x = nx, nex.y = ny;
			vis[nx][ny][nex.box[0][0]][nex.box[0][1]][nex.box[1][0]][nex.box[1][1]][nex.box[2][0]][nex.box[2][1]] = 1;
			q.push(nex);
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d", &n, &m)) {
		s = Node();
		for (int i = 0; i < n; i++)
			scanf("%s", s.map[i]);
		int t = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (s.map[i][j] == 'X') {
					s.x = i;
					s.y = j;
				}
				if (s.map[i][j] == '*') {
					s.box[t][0] = i;
					s.box[t++][1] = j;
				}
			}
		}
		int ans = bfs();
		cout << ans << endl;
	}
	return 0;
}
