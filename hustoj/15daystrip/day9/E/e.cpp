#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
long long dp[125][125];
int solve() {
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i <= n; i++)
		dp[1][i] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			for (int k = 0; k <= n && j + k <= n; k += i) {
				dp[i][j + k] += dp[i - 1][j];
			}
		}

	}
	return dp[n][n];
}

int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d", &n)) {
		long long ans = solve();
		printf("%lld\n", ans);
	}


	return 0;
}
