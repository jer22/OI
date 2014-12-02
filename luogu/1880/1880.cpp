#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 110

using namespace std;

int n;
int arr[MAXN];
int sum[MAXN];
int dp1[MAXN][MAXN];
int dp2[MAXN][MAXN];

// 从i开始再数j个数的和
int summary(int i, int j) {
	if (i + j >= n) {
		return summary(i, n - i - 1) + summary(0, (i + j) % n);
	} else {
		return sum[i + j] - (i ? sum[i - 1] : 0);
	}
}

int main( void ) {
	freopen("1880.in", "r", stdin);
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
			dp1[i][j] = 0;
			dp2[i][j] = 0x3f3f3f3f;
			for (int k = 0; k < j; k++) {
				dp1[i][j] = max(dp1[i][j], dp1[i][k] + dp1[(i + k + 1) % n][j - k - 1] + summary(i, j));
				dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[(i + k + 1) % n][j - k - 1] + summary(i, j));
			}
		}
	}
	int maxval = 0, minval = 0x3f3f3f3f;
	for (int i = 0; i < n; i++) {
		maxval = max(maxval, dp1[i][n - 1]);
		minval = min(minval, dp2[i][n - 1]);
	}
	printf("%d\n%d\n", minval, maxval);
	return 0;
}
