#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int hire, sala, fire;
int arr[15];
int dp[15][10000];
int main() {
	freopen("1158.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		scanf("%d %d %d", &hire, &sala, &fire);
		int maxn = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			maxn = max(maxn, arr[i]);
		}
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 0; i <= maxn; i++)
			dp[0][i] = i * hire;
		for (int i = 1; i <= n; i++) {
			for (int j = arr[i]; j <= maxn; j++) {
				for (int k = arr[i - 1]; k <= maxn; k++) {
					if (k < j) {
						dp[i][j] = min(dp[i][j], dp[i - 1][k] + hire * (j - k) + sala * j);
					} else if (k == j) {
						dp[i][j] = min(dp[i][j], dp[i - 1][k] + sala * j);
					} else if (k > j) {
						dp[i][j] = min(dp[i][j], dp[i - 1][k] + fire * (k - j) + sala * j);
					}
				}
			}
		}
		int ans = 0x3f3f3f3f;
		for (int j = arr[n]; j <= maxn; j++) {
			ans = min(ans, dp[n][j]);
		}
		cout << ans << endl;
	}
	return 0;
}
