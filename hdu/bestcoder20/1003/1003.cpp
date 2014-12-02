#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int T;
int n, m;
int a[1010];
int b[1010];
int height[1010][1010];
int dp[1010][1010];
int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		memset(height, 0, sizeof(height));
		memset(dp, 0, sizeof(dp));
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a[i], &b[i]);
		}
		height[1][m] = a[1];
		height[1][m - 1] = b[1]; 
		dp[1][m] = 1;
		if (m) dp[1][m - 1] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j <= m; j++) {
				if (!dp[i][j]) continue;
				if (a[i + 1] > height[i][j]) {
					if (dp[i + 1][j] < dp[i][j] + 1) {
						dp[i + 1][j] = dp[i][j] + 1;
						height[i + 1][j] = a[i + 1];
					}
				} else {
					if (dp[i + 1][j] < dp[i][j]) {
						dp[i + 1][j] = dp[i][j];
						height[i + 1][j] = height[i][j];
					}
					
				}
				if (b[i + 1] > height[i][j]) {
					if (j) {
						if (dp[i + 1][j - 1] < dp[i][j] + 1) {
							dp[i + 1][j - 1] = dp[i][j] + 1;
							height[i + 1][j - 1] = b[i + 1];
						}
					}
				} else {
					if (j) {
						if (dp[i + 1][j - 1] < dp[i][j]) {
							dp[i + 1][j - 1] = dp[i][j];
							height[i + 1][j - 1] = height[i][j];
						}
						
					}
				}
			}
		}
		// printf("%d", dp[5][0]);
		int maxx = 0;
		for (int j = 0; j <= m; j++) {
			maxx = max(maxx, dp[n][j]);
			// printf("%d ", dp[n][j]);
		}
		printf("%d\n", maxx);
	}


	return 0;
}
