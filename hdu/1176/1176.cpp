#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[100005][12];
int dp[100005][12];
int main() {
	while (~scanf("%d", &n) && n) {
		memset(arr, 0, sizeof(arr));
		memset(dp, 0, sizeof(dp));
		int a, b;
		int ed = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			arr[b][a]++;
			ed = max(ed, b);
		}
		int ans = 0;
		dp[1][4] = arr[1][4];
		dp[1][5] = arr[1][5];
		dp[1][6] = arr[1][6];
		for (int i = 2; i <= ed; i++) {
			for (int j = 0; j <= 10; j++) {
				dp[i][j] = dp[i - 1][j] + arr[i][j];
				if (j) dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + arr[i][j]);
				if (j < 10) dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] + arr[i][j]);
			}
		}
		for (int j = 0; j <= 10; j++) {
			ans = max(ans, dp[ed][j]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
