#include <bits/stdc++.h>

using namespace std;

int T, n, m;
int arr[1005][1005];
int dp[1005][1005];
int main() {
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> arr[i][j];
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
			for (int j = m; j >= 1; j--)
				dp[i][j] = max(dp[i - 1][j + 1] + arr[i][j], max(dp[i - 1][j], dp[i][j + 1]));
		cout << dp[n][1] << endl;
	}

	return 0;
}
