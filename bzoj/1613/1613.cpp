#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int dp[10002][502];
int d[10002];
int main() {
	freopen("1613.in", "r", stdin);
	scanf("%d %d", &n, &m);
	memset(dp, -1, sizeof(dp));
	for (int i = 1; i <= n; i++)
		scanf("%d", &d[i]);
	dp[0][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++) {
			if (dp[i][j] == -1) continue;
			if (j < m) dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + d[i + 1]);
			if (j && i + j <= n) dp[i + j][0] = max(dp[i + j][0], dp[i][j]);
			if (!j) dp[i + 1][0] = max(dp[i + 1][0], dp[i][j]);
		}
	}
	printf("%d\n", dp[n][0]);

	return 0;
}
