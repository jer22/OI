#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, K, s;
int a[155];
int dp[2][155][155 * 155 * 2];
int main() {
	freopen("g.in", "r", stdin);
	cin >> n >> K >> s;
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	memset(dp, 0x3f, sizeof(dp));
	dp[1][1][1] = a[1];
	dp[1][0][0] = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= min(i, K); j++) {
			for (int k = 0; k <= n * n; k++) {
				dp[i & 1][j][k] = dp[(i + 1) & 1][j][k];
				if (k - i >= 0 && j)
					dp[i & 1][j][k] = min(dp[i & 1][j][k], dp[(i + 1) & 1][j - 1][k - i] + a[i]);
			}
		}
	}
	// cout << dp[1][1][1];
	int ans = 0x3f3f3f3f;
	for (int i = 0; ((i - s) * 2) <= (K * (K + 1)); i++) {
		// cout << dp[n & 1][K][i] << endl;
		if (i > n * n) break;
		ans = min(ans, dp[n & 1][K][i]);
	}
	cout << ans << endl;
	// for (int i = )


	return 0;
}
