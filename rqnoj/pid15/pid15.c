#include <stdio.h>

int dp[1023][120];
int arr[120];
int value[120];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	int n, m;
	scanf("%d %d", &m, &n);
	int i, j;
	for (i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i], &value[i]);
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (i >= arr[j]) {
				dp[i][j] = max(dp[i][j - 1], dp[i - arr[j]][j - 1] + value[j]);
			} else {
				dp[i][j] = dp[i][j - 1];
			}
		}
	}
	printf("%d", dp[m][n]);

	system("pause");
	return 0;
}
