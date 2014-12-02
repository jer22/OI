#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

#define MAXN 110

using namespace std;

int n, m;
char arr[MAXN][MAXN];
int cnt = 0;
int color[MAXN][MAXN];

void dfs(int x, int y) {
	for (int i = x - 2; i <= x + 2; i++) {
		for (int j = y - 2; j <= y + 2; j++) {
			if (i >= 0 && i < n && j >= 0 && j < m && abs(x - i) + abs(y - j) <= 2) {
				if (arr[i][j] == '#' && !color[i][j]) {
					color[i][j] = cnt + 1;
					dfs(i, j);
				}
			}
		}
	}
}

int main() {
	freopen("1454.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", &arr[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == '#' && !color[i][j]) {
				color[i][j] = cnt + 1;
				dfs(i, j);
				cnt++;
			}
		}
	}

	printf("%d\n", cnt);
	return 0;
}
