#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
int arr[22][1005];
int dp[22][1005];
int main() {
	freopen("2571.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> arr[i][j];
				dp[i][j] = -1111111;
			}
		}
		dp[1][1] = arr[1][1];
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + arr[i + 1][j]);
				dp[i][j + 1] = max(dp[i][j + 1], dp[i][j] + arr[i][j + 1]);
				for (int k = j + j; k <= m; k += j) {
					dp[i][k] = max(dp[i][k], dp[i][j] + arr[i][k]);
				}
			}
		}
		cout << dp[n][m] << endl;
	}
	return 0;
}
