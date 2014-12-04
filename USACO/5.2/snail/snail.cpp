/*
ID:shijiey1
LANG:C++
PROG:snail
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[123][123];

int cnt = 0;
int maxcnt = 0;
int vis[123][123];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
void dfs(int x, int y, int pos) {
	if (vis[x][y]) {
		maxcnt = max(maxcnt, cnt);
		return;
	}
	vis[x][y] = 1;
	cnt++;
	// can go straight
	if (x + dx[pos] >= 1 && x + dx[pos] <= n && y + dy[pos] >= 1 && y + dy[pos] <= n && !arr[x + dx[pos]][y + dy[pos]]) {
		dfs(x + dx[pos], y + dy[pos], pos);
	} else {
		for (int i = 0; i < 4; i++) {
			if (i == pos) continue;
			if (x + dx[i] >= 1 && x + dx[i] <= n && y + dy[i] >= 1 && y + dy[i] <= n && !arr[x + dx[i]][y + dy[i]]) {
				dfs(x + dx[i], y + dy[i], i);
			}
		}
	}
	vis[x][y] = 0;
	cnt--;
}

int main() {
	freopen("snail.in", "r", stdin);
	freopen("snail.out", "w", stdout);
	scanf("%d %d", &n, &m);
	char c;
	int t;
	for (int i = 0; i < m; i++) {
		cin >> c >> t;
		arr[t][c - 'A' + 1] = 1;
	}
	
	if (n > 1 && !arr[1][2]) {
		dfs(1, 1, 3);
	}
	if (n > 1 && !arr[2][1]) {
		dfs(1, 1, 1);
	}
	cout << maxcnt << endl;
	return 0;
}
