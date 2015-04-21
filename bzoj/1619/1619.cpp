#include <bits/stdc++.h>

using namespace std;

int n, m;
int arr[705][705];
int dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
int ncol = 0, colors[705][705];
bool ishill[500000], vis[705][705];

bool check(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= m);
}

void floodfill(int x, int y, int col) {
	vis[x][y] = 1;
	colors[x][y] = col;
	for (int i = 0; i < 8; i++) {
		int nx = x + dir[i][0];
		int ny = y + dir[i][1];
		if (!check(nx, ny)) continue;
		if (arr[nx][ny] > arr[x][y]) {
			ishill[col] = 1;
		}
		if (!vis[nx][ny] && arr[nx][ny] == arr[x][y]) floodfill(nx, ny, col);
	}
}

int main() {
	freopen("1619.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> arr[i][j];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vis[i][j]) {
				floodfill(i, j, ++ncol);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= ncol; i++)
		ans += !ishill[i];
	cout << ans << endl;
	return 0;
}
