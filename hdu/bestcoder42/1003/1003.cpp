#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m, K;
int arr[105][105];
int dp[105][105][105];
int main() {
	freopen("1003.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &m, &K)) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &arr[i][j]);
		memset(dp, 0, sizeof(dp));
		dp[1][1][0] = 1;
		if (arr[1][1] <= K) dp[1][1][arr[1][1]] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int k = 0; k <= K; k++) {
					if (!dp[i][j][k]) continue;
					dp[i + 1][j][k] = 1;
					if (k + arr[i + 1][j] <= K)
						dp[i + 1][j][k + arr[i + 1][j]] = 1;
					dp[i][j + 1][k] = 1;
					if (k + arr[i][j + 1] <= K)
						dp[i][j + 1][k + arr[i][j + 1]] = 1;
				}
			}
		}
		int k;
		for (k = K; K >= 0; k--)
			if (dp[n][m][k]) break;
		printf("%d\n", k);
	}


	return 0;
}
