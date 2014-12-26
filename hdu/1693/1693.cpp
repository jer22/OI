#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
int map[12][12];
long long dp[12][1 << 12];
int main() {
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &map[i][j]);
		memset(dp, 0, sizeof(dp));
		dp[m][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int k = 0; k < (1 << m); k++)
				dp[0][k << 1] = dp[m][k];
			for (int j = 1; j <= m; j++) {
				for (int k = 0; k < (1 << m + 1); k++) {
					int x = 1 << j - 1;
					int y = 1 << j;
					bool p = x & k;
					bool q = y & k;
					if (!map[i][j]) {
						if (!p && !q) dp[j][k] = dp[j - 1][k];
						else dp[j][k] = 0;
					} else {
						if (p == q) dp[j][k] = dp[j - 1][k ^ x ^ y];
						else dp[j][k] = dp[j - 1][k] + dp[j - 1][k ^ x ^ y];
					}
				}
			}
		}
		printf("Case %d: There are %I64d ways to eat the trees.\n", cas++, dp[m][0]);
	}
	return 0;
}
