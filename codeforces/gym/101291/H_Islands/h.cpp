#include <bits/stdc++.h>

using namespace std;

int n, m;
char arr[200][100];
bool vis[100][400];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void dfs(int x, int y) {
	vis[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0], ny = y + dir[i][1];
		if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
		if (!vis[nx][ny] && arr[nx][ny] != 'W') dfs(nx, ny);
	}
}

int main() {
	freopen("h.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vis[i][j] && arr[i][j] == 'L') {
				dfs(i, j);
				ans++;
			}
		}
	}
	cout << ans << endl;


	return 0;
}
