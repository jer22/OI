#include <bits/stdc++.h>

using namespace std;

int n, m, b, MOD;
int arr[505];
int dp[505][505];
int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> m >> b >> MOD;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = arr[i]; k <= b; k++) {
				dp[j][k] += dp[j - 1][k - arr[i]];
				dp[j][k] %= MOD;
			}
		}
	}
	int ans = 0;
	for (int i = 0; i <= b; i++) {
		ans += dp[m][i];
		ans %= MOD;
	}
	cout << ans << endl;
	return 0;
}
