#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
short arr[105][105];
short dp[105][105];
int dfs(int x, int y) {
	if (dp[x][y] != -1) return dp[x][y];
	int ans = 0, temp = (arr[x][y] + 100) * (100 - arr[x][y] + 1) / 2 - arr[x][y];
	for (int nx = max(x-k,1); nx <= min(n,x+k); nx++) {
		if (nx == x) continue;
		if (arr[nx][y] > arr[x][y])
			ans = max(ans, dfs(nx, y));
		if (ans == temp) {
			dp[x][y] = ans + arr[x][y];
			return dp[x][y];
		}
	}
	for (int ny = max(y-k,1); ny <= min(n,y+k); ny++) {
		if (ny == y) continue;
		if (arr[x][ny] > arr[x][y])
			ans = max(ans, dfs(x, ny));
		if (ans == temp) {
			dp[x][y] = ans + arr[x][y];
			return dp[x][y];
		}
	}
	dp[x][y] = ans + arr[x][y];
	return dp[x][y];
}

int main() {
	freopen("1078.in", "r", stdin);
	while (~scanf("%d %d", &n, &k)) {
		if (n == -1 || k == -1) break;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				scanf("%hd", &arr[i][j]);
				dp[i][j]=-1;
			}
		int ans = 0;
		dfs(1, 1);
		printf("%hd\n", dp[1][1]);
	}


	return 0;
}
