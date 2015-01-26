/*
ID:shijiey1
LANG:C++
PROG:wissqu
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	char c;
	int x, y;
};

char field[6][6];
int cnt[6];
int ansnum = 0;
Node ans[18];
bool vis[6][6];
int dir[9][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

bool check(int x, int y, char c) {
	if (vis[x][y]) return false;
	for (int i = 0; i < 9; i++)
		if (field[x + dir[i][0]][y + dir[i][1]] == c)
			return false;
	return true;
}

void dfs(int step) {
	if (step == 16) {
		if (!ansnum) {
			for (int i = 0; i < 16; i++)
				cout << ans[i].c << ' ' << ans[i].x << ' ' << ans[i].y << endl;
		}
		ansnum++;
		return;
	}
	for (int c = 1; c <= 5; c++) {
		if (!cnt[c]) continue;
		cnt[c]--;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (!check(i, j, c + 'A' - 1)) continue;
				vis[i][j] = 1;
				char temp = field[i][j];
				field[i][j] = c + 'A' - 1;
				ans[step].x = i;
				ans[step].y = j;
				ans[step].c = c + 'A' - 1;
				dfs(step + 1);
				field[i][j] = temp;
				vis[i][j] = 0;
			}
		}
		cnt[c]++;
	}
}

int main() {
	freopen("wissqu.in", "r", stdin);
	freopen("wissqu.out", "w", stdout);
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
			cin >> field[i][j];
	for (int i = 1; i <= 5; i++)
		cnt[i] = 3;
	for (int i = 1; i <= 4; i++) {
		for (int j = 1; j <= 4; j++) {
			if (check(i, j, 'D')) {
				char c = field[i][j];
				field[i][j] = 'D';
				vis[i][j] = 1;
				ans[0].c = 'D';
				ans[0].x = i;
				ans[0].y = j;
				dfs(1);
				field[i][j] = c;
				vis[i][j] = 0;
			}
		}
	}
	cout << ansnum << endl;
	return 0;
}
