#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

struct Node{
	string stat;
	int x, y, step;
	Node() {}
	Node(int a, int b, int c, string d) : x(a), y(b), step(c), stat(d) {}
};

int n, sx, sy, ex, ey;
char g[11][11];
int arr[11][11];
int box[11][11];
Point boxes[70];
int nbox;
map<string, bool> vis[11][11];
int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

bool inrange(int x, int y) { return x >= 1 && x <= n && y >= 1 && y <= n; }
bool check(int x, int y, string stat) {
	if (box[x][y] != -1 && stat[box[x][y]] == '0') return true;
	for (int i = 1; i <= 4; i++) {
		if (inrange(x, y + i)) {
			if (arr[x][y + i] >= i && stat[box[x][y + i]] == '1') return true;
		}
		if (inrange(x, y - i)) {
			if (arr[x][y - i] >= i && stat[box[x][y - i]] == '3') return true;
		}
		if (inrange(x + i, y)) {
			if (arr[x + i][y] >= i && stat[box[x + i][y]] == '2') return true;
		}
		if (inrange(x - i, y)) {
			if (arr[x - i][y] >= i && stat[box[x - i][y]] == '4') return true;
		}
	}
	return false;
}

int spfa(string s) {
	queue<Node> q;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			vis[i][j].clear();
	q.push(Node(sx, sy, 0, s));
	vis[sx][sy][s] = 1;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dir[i][0];
			int ny = cur.y + dir[i][1];
			if (nx == ex && ny == ey) {
				// cout << cur.stat << endl;
				return cur.step + 1;
			}
			if (!inrange(nx, ny)) continue;
			if (check(nx, ny, cur.stat)) {
				if (!vis[nx][ny][cur.stat]) {
					vis[nx][ny][cur.stat] = 1;
					q.push(Node(nx, ny, cur.step + 1, cur.stat));
				}
			}
			if (box[cur.x][cur.y] != -1 && cur.stat[box[cur.x][cur.y]] == '0') {
				bool flag = true;
				for (int j = 1; j <= arr[cur.x][cur.y]; j++) {
					int nnx = cur.x + j * dir[i][0];
					int nny = cur.y + j * dir[i][1];
					if (!inrange(nnx, nny) || check(nnx, nny, cur.stat) || g[nnx][nny] == 'E') {
						flag = false;
						break;
					}
				}
				if (flag) {
					string nex = cur.stat;
					nex[box[cur.x][cur.y]] = i + 1 + '0';
					if (!vis[nx][ny][nex]) {
						vis[nx][ny][nex] = 1;
						q.push(Node(nx, ny, cur.step + 1, nex));
					}
				}
			}
		}
	}
	return -1;
}

int main() {
	freopen("escape.in", "r", stdin);
	freopen("escape.out", "w", stdout);
	while (~scanf("%d %d %d", &n, &sx, &sy) && n && sx && sy) {
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);
		nbox = 0;
		memset(box, -1, sizeof(box));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (g[i][j] == 'E') {
					ex = i, ey = j;
					arr[i][j] = 1;
				} else if (g[i][j] != '.') {
					arr[i][j] = g[i][j] - '0';
					box[i][j] = nbox;
					boxes[nbox++] = Point(i, j);
				} else arr[i][j] = 0;
			}
		}
		if (g[sx][sy] == 'E') {
			printf("0\n");
			continue;
		}

		string s = "";
		for (int i = 0; i < nbox; i++)
			s += "0";
		int ans = spfa(s);
		if (ans == -1) printf("Impossible\n");
		else printf("%d\n", ans);
	}


	return 0;
}
