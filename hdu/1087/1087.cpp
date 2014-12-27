#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[1005];
int dp[1005];
int main() {
	freopen("1087.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			cin >> arr[i];
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
			dp[i] = arr[i];
		int ans = dp[1];
		for (int i = 2; i <= n; i++) {
			for (int j = i - 1; j >= 1; j--) {
				if (arr[j] >= arr[i]) continue;
				dp[i] = max(dp[i], dp[j] + arr[i]);
			}
			ans = max(ans, dp[i]);
		}
		cout << ans << endl;
	}
	return 0;
}
