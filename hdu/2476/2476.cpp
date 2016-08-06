#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string a, b;
int dp[105][105], ans[105];
int main() {
	freopen("2476.in", "r", stdin);
	while (cin >> a) {
		cin >> b;
		int n = a.length();
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < n; i++)
			dp[i][i] = 1;
		for (int len = 2; len <= n; len++) {
			for (int i = 0; i < n - len + 1; i++) {
				int j = i + len - 1;
				dp[i][j] = dp[i + 1][j] + 1;
				for (int k = i + 1; k <= j; k++) {
					if (b[i] == b[k]) dp[i][j] = min(dp[i][j], dp[i + 1][k] + dp[k + 1][j]);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			ans[i] = dp[0][i];
		}
		for (int i = 0; i < n; i++) {
			if (a[i] == b[i]) {
				ans[i] = min(ans[i], ans[i - 1]);
			} else {
				for (int j = 0; j < i; j++)
					ans[i] = min(ans[i], ans[j] + dp[j + 1][i]);
			}
		}
		cout << ans[n - 1] << endl;
	}


	return 0;
}
