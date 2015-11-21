#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[1005][1005];
long long dp[1005][1005];
int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &arr[i][j]);
				dp[i][j] = 1000000000000000000ll;
			}
		}
		if (n == 1 && m == 2) {
			printf("%d\n", arr[1][1] * arr[1][2]);
			continue;
		}
		if (n == 2 && m == 1) {
			printf("%d\n", arr[1][1] * arr[2][1]);
			continue;
		}
		dp[1][2] = (long long)arr[1][1] * arr[1][2];
		dp[2][1] = (long long)arr[1][1] * arr[2][1];
		for (int i = 4; i <= n; i += 2) dp[1][i] = min(dp[1][i], dp[1][i - 2] + (long long)arr[1][i - 1] * arr[1][i]);
		for (int j = 4; j <= m; j += 2) dp[j][1] = min(dp[j][1], dp[j - 2][1] + (long long)arr[j - 1][1] * arr[j][1]);
		for (int i = 2; i <= n; i++) {
			for (int j = 2; j <= m; j++) {
				if (!((i + j) & 1)) continue;
				if (i > 2) dp[i][j] = min(dp[i][j], dp[i - 2][j] + (long long)arr[i - 1][j] * arr[i][j]);
				if (i > 1 && j > 1) {
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (long long)arr[i - 1][j] * arr[i][j]);
					dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (long long)arr[i][j - 1] * arr[i][j]);
				}
				if (j > 2) dp[i][j] = min(dp[i][j], dp[i][j - 2] + (long long)arr[i][j - 1] * arr[i][j]);
			}
		}
		cout << dp[n][m] << endl;
	}


	return 0;
}
