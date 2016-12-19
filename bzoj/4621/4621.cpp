#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const int MOD = 1000000007;

int n, m;
int arr[MAXN];
int dp[MAXN][MAXN];
void solve() {
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		int l = i, r = i;
		while (l > 1 && arr[i] > arr[l - 1]) l--;
		while (r < n && arr[i] > arr[r + 1]) r++;
		(dp[i][m] += dp[i - 1][m]) %= MOD;
		for (int j = m; j >= 1; j--) {
			int now = dp[l - 1][j - 1];
			for (int k = l; k <= r; k++) {
				(dp[k][j] += now) %= MOD;
				(now += dp[k][j - 1]) %= MOD;
			}
			(dp[i][j - 1] += dp[i - 1][j - 1]) %= MOD;
			(dp[i][j] += -dp[i - 1][j - 1] + MOD) %= MOD;
		}
	}
	// cout << dp[3][1] << endl;
}

int main() {
	freopen("4621.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	solve();
	int ans = 0;
	for (int i = 0; i <= m; i++)
		(ans += dp[n][i]) %= MOD;
	printf("%d\n", ans);


	return 0;
}
