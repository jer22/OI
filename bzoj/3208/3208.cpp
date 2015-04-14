#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, q;
int arr[705][705];
bool fuck[705][705];
int dp[705][705];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= n && !fuck[x][y];
}

int dfs(int x, int y) {
	if (dp[x][y]) return dp[x][y];
	dp[x][y] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = x + dir[i][0], ny = y + dir[i][1];
		if (check(nx, ny) && arr[nx][ny] < arr[x][y]) {
			dp[x][y] = max(dp[x][y], dfs(nx, ny) + 1);
		}
	}
	return dp[x][y];
}

void query() {
	int ans = 0;
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (!fuck[i][j])
				ans = max(ans, dfs(i, j));
	printf("%d\n", ans);
}

void fill(int a, int b, int c, int d, int p) {
	for (int i = a; i <= c; i++)
		for (int j = b; j <= d; j++)
			fuck[i][j] = p;
}

int main() {
	freopen("3208.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &arr[i][j]);
	scanf("%d", &q);
	int a, b, c, d;
	char op[5];
	for (int i = 0; i < q; i++) {
		scanf("%s", op); 
		if (op[0] == 'Q') query();
		else {
			scanf("%d %d %d", &a, &b, &c);
			if (op[0] == 'C') arr[a][b] = c;
			else {
				scanf("%d", &d);
				if (op[0] == 'S') fill(a, b, c, d, 1);
				else fill(a, b, c, d, 0);
			}
		}

	}


	return 0;
}
