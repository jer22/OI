#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int arr[200005];
int dp[200005];
int tot[200005];
int main() {
	freopen("1422.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a, &b);
			arr[n + i] = arr[i] = a - b;
		}
		memset(dp, 0, sizeof(dp));
		memset(tot, 0, sizeof(tot));
		int ans = 0;
		for (int i = 1; i <= n << 1; i++) {
			if (tot[i - 1] + arr[i] < 0) {
				dp[i] = 0;
				tot[i] = 0;
			} else {
				dp[i] = dp[i - 1] + 1;
				tot[i] = tot[i - 1] + arr[i];
			}
			ans = max(ans, dp[i]);
			if (ans == n) break;
		}
		cout << ans << endl;
	}


	return 0;
}
