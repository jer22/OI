#include <bits/stdc++.h>

using namespace std;

const int MOD = 1024523;

int n, m;
int dp[505][505][505];
char a[505], b[505];

int main() {
	freopen("1566.in", "r", stdin);
	scanf("%d %d", &n, &m);
	scanf("%s %s", a + 1, b + 1);
	reverse(a + 1, a + n + 1);
	reverse(b + 1, b + m + 1);
	dp[0][0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= n; k++) {
				int l = i + j - k;
				if (l < 0 || l > m) continue;
				if (a[i + 1] == a[k + 1]) (dp[i + 1][j][k + 1] += dp[i][j][k]) %= MOD;
				if (a[i + 1] == b[l + 1]) (dp[i + 1][j][k] += dp[i][j][k]) %= MOD;
				if (b[j + 1] == a[k + 1]) (dp[i][j + 1][k + 1] += dp[i][j][k]) %= MOD;
				if (b[j + 1] == b[l + 1]) (dp[i][j + 1][k] += dp[i][j][k]) %= MOD;
			}
		}
	}
	printf("%d\n", dp[n][m][n]);

	return 0;
}
