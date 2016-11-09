#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 10005;
const int MOD = 100000007;

int T, n;
char str[MAXN];
long long dp[MAXN][2/*up*/][2/*down*/][3/*need*/];
int arr[MAXN];

int main() {
	// freopen("5965.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%s", str + 1);
		n = strlen(str + 1);
		for (int i = 1; i <= n; i++)
			arr[i] = str[i] - '0';
		memset(dp, 0, sizeof(dp));
		// dp[0][0][0][0] = 1;
		if (arr[1] >= 0 && arr[1] <= 2)
			dp[1][0][0][arr[1]] = 1;
		if (arr[1] - 1 >= 0 && arr[1] - 1 <= 2) {
			dp[1][0][1][arr[1] - 1] = 1;
			dp[1][1][0][arr[1] - 1] = 1;
		}
		if (arr[1] - 2 >= 0 && arr[1] - 2 <= 2) {
			dp[1][1][1][arr[1] - 2] = 1;
		}
		for (int i = 1; i < n; i++) {
			for (int u = 0; u < 2; u++) {
				for (int d = 0; d < 2; d++) {
					if (dp[i][u][d][0]) {
						int nw = arr[i + 1] - u - d;
						if (nw >= 0 && nw <= 2)
							(dp[i + 1][0][0][nw] += dp[i][u][d][0]) %= MOD;
					}
					if (dp[i][u][d][1]) {
						int nw = arr[i + 1] - u - d - 1;
						if (nw >= 0 && nw <= 2) {
							(dp[i + 1][0][1][nw] += dp[i][u][d][1]) %= MOD;
							(dp[i + 1][1][0][nw] += dp[i][u][d][1]) %= MOD;
						}
					}
					if (dp[i][u][d][2]) {
						int nw = arr[i + 1] - u - d - 2;
						if (nw >= 0 && nw <= 2)
							(dp[i + 1][1][1][nw] += dp[i][u][d][2]) %= MOD;
					}
				}
			}
		}
		long long ans = (dp[n][0][0][0] + dp[n][0][1][0] + dp[n][1][0][0] + dp[n][1][1][0]) % MOD;
		printf("%lld\n", ans);
	}
	return 0;
}
