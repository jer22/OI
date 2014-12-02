#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[35][35];

void dfs (int x, int y) {
	arr[x][y] = 0;
	if (x > 1 && arr[x - 1][y] == 2) {
		dfs(x - 1, y);
	}
	if (x < n && arr[x + 1][y] == 2) {
		dfs(x + 1, y);
	}
	if (y > 1 && arr[x][y - 1] == 2) {
		dfs(x, y - 1);
	}
	if (y < n && arr[x][y + 1] == 2) {
		dfs(x, y + 1);
	}
}

int main() {
	freopen("1162.in", "r", stdin);
	scanf("%d", &n);
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &t);
			if (!t) {
				t = 2;
			}
			arr[i][j] = t;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (arr[1][i] == 2) {
			dfs(1, i);
		}
		if (arr[i][1] == 2) {
			dfs(i, 1);
		}
		if (arr[n][i] == 2) {
			dfs(n, i);
		}
		if (arr[i][n] == 2) {
			dfs(i, n);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			printf("%d", arr[i][j]);
			if (j != n) {
				printf(" ");
			}
		}
		printf("\n");
	}
	return 0;
}
