#include <stdio.h>
#include <stdlib.h>

int dp[20124][1000];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	int v, n;
	int arr[40];
	int i, j;
	scanf("%d %d", &v, &n);
	for (i = 1; i <= n; i ++) {
		scanf("%d", &arr[i]);
	}
	for (i = 1; i <= v; i++) {
		for (j = 1; j <= n; j++) {
			if (i >= arr[j])
				dp[i][j] = max(dp[i][j - 1], dp[i - arr[j]][j - 1] + arr[j]);
			else
				dp[i][j] = dp[i][j - 1];
		}
	}

	printf("%d", v - dp[v][n]);
	return 0;
}
