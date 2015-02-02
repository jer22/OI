#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int r, b, g, m, n, p;
int X[65];
int vis[65];
int loop[65];
int dp[22][22][22];

int power(int a, int b) {
	int ans = 1, base = a;
	while (b) {
		if (b & 1) {
			ans *= base;
			ans %= p;
		}
		b >>= 1;
		base *= base;
		base %= p;
	}
	return ans;
}

int polya() {
	memset(vis, 0, sizeof(vis));
	memset(loop, 0, sizeof(loop));
	int num = 0;
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			loop[++num] = 1;
			vis[i] = 1;
			for (int pos = X[i]; !vis[pos]; pos = X[pos]) {
				vis[pos] = 1;
				loop[num]++;
			}
		}
	}
	return num;
}

int solve() {
	int num = polya();
	memset(dp, 0, sizeof(dp));
	dp[0][0][0] = 1;
	for (int w = 1; w <= num; w++) {
		for (int i = r; i >= 0; i--) {
			for (int j = b; j >= 0; j--) {
				for (int k = g; k >= 0; k--) {
					if (i - loop[w] >= 0) dp[i][j][k] += dp[i - loop[w]][j][k];
					dp[i][j][k] %= p;
					if (j - loop[w] >= 0) dp[i][j][k] += dp[i][j - loop[w]][k];
					dp[i][j][k] %= p;
					if (k - loop[w] >= 0) dp[i][j][k] += dp[i][j][k - loop[w]];
					dp[i][j][k] %= p;
				}
			}
		}
	}
	return dp[r][b][g];
}

int main() {
	freopen("1004.in", "r", stdin);
	scanf("%d %d %d %d %d", &r, &b, &g, &m, &p);
	n = r + b + g;
	int ans = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			cin >> X[j];
		ans += solve();
		ans %= p;
	}
	for (int i = 1; i <= n; i++) X[i] = i;
	ans += solve();
	ans %= p;
	ans *= power(m + 1, p - 2) % p;
	printf("%d\n", ans % p);
	return 0;
}
