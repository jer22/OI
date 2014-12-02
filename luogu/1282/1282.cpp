#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[1010][2];
int dp[1010][20000];
int sum = 0;
int main() {
	freopen("1282.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
		sum += arr[i][0];
		sum += arr[i][1];
	}
	memset(dp, -1, sizeof(dp));
	dp[1][arr[1][0]] = 0;
	dp[1][arr[1][1]] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= sum; j++) {
			if (j >= arr[i][0] && dp[i - 1][j - arr[i][0]] != -1) {
				if (dp[i][j] == -1)
					dp[i][j] = dp[i - 1][j - arr[i][0]];
				else dp[i][j] = min(dp[i][j], dp[i - 1][j - arr[i][0]]);
			}
			if (j >= arr[i][1] && dp[i - 1][j - arr[i][1]] != -1) {
				if (dp[i][j] == -1)
					dp[i][j] = dp[i - 1][j - arr[i][1]] + 1;
				else dp[i][j] = min(dp[i][j], dp[i - 1][j - arr[i][1]] + 1);
			}
		}
		// for (int j = 1; j <= sum; j++) {
		// 	printf("%d %d\n", j, dp[i][j]);
		// }
		// printf("\n");
	}
	int ans = 0;
	dp[n][0] = 0x3f3f3f3f;
	for (int i = sum >> 1; i >= 1; i--) {
		int j = sum - i;
		if (dp[n][i] != -1 || dp[n][j] != -1) {
			if (dp[n][i] == -1) {
				ans = dp[n][j];
			} else if (dp[n][j] == -1) {
				ans = dp[n][i];
			} else ans = min(dp[n][i], dp[n][j]);
			break;
		}
	}
	printf("%d\n", ans);
	return 0;
}
