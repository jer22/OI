/*
ID:shijiey1
PROG:castle
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int arr[55][55];
int color[55][55];
int cnt[3000];
int curColor = 0;

void dfs(int x, int y) {
	if (x > 1 && !(arr[x][y] & 2) && !color[x - 1][y]) {
		color[x - 1][y] = curColor;
		cnt[curColor]++;
		dfs(x - 1, y);
	}
	if (x < n && !(arr[x][y] & 8) && !color[x + 1][y]) {
		color[x + 1][y] = curColor;
		cnt[curColor]++;
		dfs(x + 1, y);
	}
	if (y > 1 && !(arr[x][y] & 1) && !color[x][y - 1]) {
		color[x][y - 1] = curColor;
		cnt[curColor]++;
		dfs(x, y - 1);
	}
	if (y < m && !(arr[x][y] & 4) && !color[x][y + 1]) {
		color[x][y + 1] = curColor;
		cnt[curColor]++;
		dfs(x, y + 1);
	}
}

int main() {
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!color[i][j]) {
				curColor++;
				color[i][j] = curColor;
				cnt[curColor]++;
				dfs(i, j);
			}
		}
	}
	int x, y;
	int ans = 0;
	char c = 'E';
	
	for (int j = 1; j <= m; j++) {
		for (int i = n; i >= 1; i--) {
			if (i > 1 && (arr[i][j] & 2) && color[i][j] != color[i - 1][j]) {
				if (cnt[color[i][j]] + cnt[color[i - 1][j]] > ans) {
					ans = cnt[color[i][j]] + cnt[color[i - 1][j]];
					x = i;
					y = j;
					c = 'N';
				}
			}
			if (j < m && (arr[i][j] & 4) && color[i][j] != color[i][j + 1]) {
				if (cnt[color[i][j]] + cnt[color[i][j + 1]] > ans) {
					ans = cnt[color[i][j]] + cnt[color[i][j + 1]];
					x = i;
					y = j;
					c = 'E';
				}
			}
		}
	}
	sort(cnt + 1, cnt + 1 + curColor);
	printf("%d\n%d\n", curColor, cnt[curColor]);
	printf("%d\n%d %d %c\n", ans, x, y, c);

	return 0;
}
