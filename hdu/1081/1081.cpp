#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int sum[105][105];
int dp[105][105][105];
int main() {
	freopen("1081.in", "r", stdin);
	while (cin >> n) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				scanf("%d", &sum[i][j]);
				sum[i][j] += sum[i][j - 1];
			}
		}
		for (int j = 1; j <= n; j++) {
			for (int k = j; k >= 1; k--) {
				dp[1][j][k] = sum[1][j] - sum[1][j - k];
			}
		}
		int ans = -0x3f3f3f3f;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				for (int k = j; k >= 1; k--) {
					dp[i][j][k] = max(sum[i][j] - sum[i][j - k], sum[i][j] - sum[i][j - k] + dp[i - 1][j][k]);
					ans = max(ans, dp[i][j][k]);
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
