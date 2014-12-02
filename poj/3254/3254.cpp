#include <cstdio>
#include <cstring>
#include <algorithm>

#define MOD 100000000

using namespace std;

int n, m;
int arr[15][15];
long long dp[15][5005];

void dfs(int i, int j, int stat, int pre) {
	if (j < 0) {
		dp[i + 1][stat] += dp[i][pre];
		dp[i + 1][stat] %= MOD;
		return;
	}
	// dont place
	dfs(i, j - 1, stat, pre);
	// if can place, then place
	if (!(pre & (1 << j)) && arr[i][m - j - 1]) {
		dfs(i, j - 2, stat | (1 << j), pre);
	}
}

int main() {
	freopen("3254.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int pre = 0; pre < 1 << m; pre++) {
			if (dp[i][pre]) {
				dfs(i, m - 1, 0, pre);
			}
		}
		// for (int j = 0; j < 1 << m; j++) {
		// 	if (dp[i][j]) {
		// 		printf("%d %d %d\n", i, j, dp[i][j]);
		// 	}
		// }
	}
	long long ans = 0;	
	for (int i = 0; i < 1 << m; i++) {
		ans += dp[n][i];
		ans %= MOD;
		// printf("%d %d\n", i, dp[n][i]);
	}
	printf("%lld\n", ans);

	return 0;
}
