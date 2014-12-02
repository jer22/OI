#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int cost[110];
int dp[110][10010];
int main () {
	freopen("1164.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cost[i]);
	}
	for (int i = 0; i <= n; i++) {
		dp[i][0] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (j >= cost[i])
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - cost[i]];
			else dp[i][j] = dp[i - 1][j];
		}
	}
	printf("%d\n", dp[n][m]);
	return 0;
}
