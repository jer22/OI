#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
int arr[2005];
int dp[2005][1005];
int main() {
	freopen("1421.in", "r", stdin);
	while (~scanf("%d %d", &n, &k)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		sort(arr + 1, arr + n + 1);
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 0; i <= n; i++)
			dp[i][0] = 0;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j * 2 <= i; j++) {
				dp[i][j] = min(dp[i - 1][j], dp[i - 2][j - 1] + (arr[i] - arr[i - 1]) * (arr[i] - arr[i - 1]));
			}
		}
		cout << dp[n][k] << endl;
	}
	return 0;
}
