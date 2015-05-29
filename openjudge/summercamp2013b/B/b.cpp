#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, s;
int lim[25];
int dp[10005][25];

int dfs(int sum, int v) {
	if (dp[sum][v] != -1) return dp[sum][v];
	int u = v + 1;
	if (u == n << 1) u = 1;
	for (int k = sum - 1; k >= 0 && sum - k <= lim[v]; k--) {
		if (!dfs(k, u)) return dp[sum][v] = 1;
	}
	return dp[sum][v] = 0;
}

int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		scanf("%d", &s);
		for (int i = 1; i <= n << 1; i++)
			scanf("%d", &lim[i]);
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n << 1; i++)
			dp[0][i] = 1, dp[1][i] = 0;
		cout << dfs(s, 1) << endl;
	}


	return 0;
}
