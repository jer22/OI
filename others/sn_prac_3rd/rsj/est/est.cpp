#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int INF = 0x7f7f7f7f;

int n, m;
int len[2005], sum[2005];
int dp[2005][2005];

int main() {
	freopen("est.in", "r", stdin);
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &len[i]);
		sum[i] = sum[i - 1] + len[i];
	}
	memset(dp, 0x7f, sizeof(dp));
	for (int i = 1; i <= n; i++) {
		if (sum[i] + i - 1 > m) break;
		dp[1][i] = 0;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			int nowlen = sum[j] - sum[i - 1] + j - i;
			if (nowlen > m) break;
			for (int k = i - 1; k >= 1; k--) {
				int prelen = sum[i - 1] - sum[k - 1] + i - k - 1;
				if (prelen > m) break;
				if (dp[k][i - 1] + abs(nowlen - prelen) < dp[i][j])
					dp[i][j] = dp[k][i - 1] + abs(nowlen - prelen);
			}
		}
	}
	int ans = 0x7f7f7f7f;
	for (int i = 1; i <= n; i++) {
		ans = min(ans, dp[i][n]);
	}
	printf("%d\n", ans);
	return 0;
}
