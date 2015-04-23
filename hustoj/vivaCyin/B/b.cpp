#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n, m;
int arr[15][15];
int dp[4105][505];

int get(int x) {
	int ans = 0;
	while (x) {
		ans += (x & 1);
		x >>= 1;
	}
	return ans;
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &arr[i][j]);
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1;
		for (int i = 0; i < 1 << n; i++) {
			int now = get(i);
			for (int j = 0; j <= m; j++) {
				if (!dp[i][j]) continue;
				for (int k = 0; k < n; k++) {
					if ((i >> k) & 1) continue;
					int t = min(j + arr[now][k], m);
					dp[i | (1 << k)][t] += dp[i][j];
				}
			}
		}
		int ans = dp[(1 << n) - 1][m];
		int tot = 1;
		for (int i = 1; i <= n; i++)
			tot *= i;
		if (!ans) printf("No solution\n");
		else {
			int gg = __gcd(tot, ans);
			printf("%d/%d\n", tot / gg, ans / gg);
		}
	}


	return 0;
}
