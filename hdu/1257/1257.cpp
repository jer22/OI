#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[2222];
int dp[2222];
int main() {
	freopen("1257.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		memset(dp, 0, sizeof(dp));
		dp[1] = 1;
		int ans = 1;
		for (int i = 2; i <= n; i++) {
			dp[i] = 1;
			for (int j = i - 1; j >= 1; j--) {
				if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
					dp[i] = dp[j] + 1;
				}
			}
			ans = max(ans, dp[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
