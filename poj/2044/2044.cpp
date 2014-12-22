#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int dir[9][2] = {{0, 0}, {-1, 0}, {-2, 0}, {0, -1}, {0, -2}, {1, 0}, {2, 0}, {0, 1}, {0, 2}};
int days[377];
int vis[377][9][7][7][7][7];

bool check(int day, int x, int y, int d1, int d2, int d3, int d4) {
	if (d1 == 7 || d2 == 7 || d3 == 7 || d4 == 7 || vis[day][3 * x + y][d1][d2][d3][d4]) return false;
	if(((1 << (4 * x + y))
		| (1 << (4 * x + y + 1))
		| (1 << (4 * (x + 1) + y))
		| (1 << (4 * (x + 1) + y + 1)))
		& days[day]) return false;
	return true;
}

bool dfs(int day, int x, int y, int d1, int d2, int d3, int d4) {
	if (day == n) return true;
	int n1 = d1, n2 = d2, n3 = d3, n4 = d4;
	n1++;
	if (x == 0 && y == 0) n1 = 0;
	n2++;
	if (x == 0 && y == 2) n2 = 0;
	n3++;
	if (x == 2 && y == 0) n3 = 0;
	n4++;
	if (x == 2 && y == 2) n4 = 0;
	if (!check(day, x, y, n1, n2, n3, n4)) return false;
	vis[day][3 * x + y][n1][n2][n3][n4] = 1;
	for (int i = 0; i < 9; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
			if (dfs(day + 1, nx, ny, n1, n2, n3, n4)) return true;
		}
	}
	return false;
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(days, 0, sizeof(days));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < n; i++) {
			int t;
			for (int j = 0; j < 16; j++) {
				scanf("%d", &t);
				days[i] <<= 1;
				days[i] |= t;
			}
		}
		int ans = dfs(0, 1, 1, 0, 0, 0, 0);
		cout << ans << endl;
	}
	return 0;
}
