#include <stdio.h>
#include <stdlib.h>

int arr[1002][1002];
int dp[1002][1002];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	int n;
	scanf("%d", &n);
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j <= i; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (i = 0; i < n; i++) {
		dp[n - 1][i] = arr[n - 1][i];
	}
	for (i = n - 2; i >= 0; i--) {
		for (j = 0; j <= i; j++) {
			dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + arr[i][j];
		}
	}
	printf("%d", dp[0][0]);
	return 0;
}
