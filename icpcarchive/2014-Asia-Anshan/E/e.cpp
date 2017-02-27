#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int T, n, m;
int arr[105];
int sc[55][55];
int dp[105][55];
int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &sc[i][j]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= m; j++)
				dp[i][j] = 0;
			if (~arr[i]) {
				if (~arr[i - 1])
					dp[i][arr[i]] = dp[i - 1][arr[i - 1]] + sc[arr[i - 1]][arr[i]];
				else {
					for (int k = 1; k <= m; k++)
						dp[i][arr[i]] = max(dp[i][arr[i]], dp[i - 1][k] + sc[k][arr[i]]);
				}
			} else {
				for (int j = 1; j <= m; j++) {
					if (~arr[i - 1])
						dp[i][j] = dp[i - 1][arr[i - 1]] + sc[arr[i - 1]][j];
					else {
						for (int k = 1; k <= m; k++)
							dp[i][j] = max(dp[i][j], dp[i - 1][k] + sc[k][j]);
					}
				}
				
			}
		}
		int ans = 0;
		for (int i = 1; i <= m; i++) {
			ans = max(ans, dp[n][i]);
		}
		printf("%d\n", ans);
	}


	return 0;
}
