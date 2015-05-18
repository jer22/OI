#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MOD = 10000;

int n, k;
int dp[1005][1005];
int sum[1005][1005];
int main() {
	freopen("2431.in", "r", stdin);
	scanf("%d %d", &n, &k);
	dp[1][0] = 1;
	for (int i = 0; i <= k; i++)
		sum[1][i] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= k; j++) {
			dp[i][j] = sum[i - 1][j];
			if (j >= i) dp[i][j] -= sum[i - 1][j - i];
			dp[i][j] += MOD;
			dp[i][j] %= MOD;
		}
		sum[i][0] = 1;
		for (int j = 1; j <= k; j++) 
			sum[i][j] = (sum[i][j - 1] + dp[i][j]) % MOD;
	}
	cout << dp[n][k] << endl;

	return 0;
}
