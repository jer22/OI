#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 1010
#define INF 0x3f3f3f3f

using namespace std;

int n;
int arr[MAXN];
int sum[MAXN];
int dp[MAXN][MAXN]; // dp[i][j]：从第i开始再数j堆进行合并的最佳方案

// 从i开始再数j个数的和
int summary(int i, int j) {
	if (i + j >= n) {
		return summary(i, n - i - 1) + summary(0, (i + j) % n);
	} else {
		return sum[i + j] - (i ? sum[i - 1] : 0);
	}
}

int main( void ) {
	freopen("stoneCombine.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sum[0] = arr[0];
	for (int i = 1; i < n; i++) {
		sum[i] = arr[i] + sum[i - 1];
	}
	for (int j = 1; j < n; j++) {
		for (int i = 0; i < n; i++) {
			dp[i][j] = INF;
			for (int k = 0; k < j; k++) {
				dp[i][j] = min(dp[i][j],
					dp[i][k] + dp[(i + k + 1) % n][j - k - 1] + summary(i, j));
			}
		}
	}
	int maxval = 0;
	for (int i = 0; i < n; i++) {
		maxval = max(maxval, dp[i][n - 1]);
	}
	printf("%d", dp[0][n - 1]);
	return 0;
}
