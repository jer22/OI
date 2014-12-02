#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dp[1002][102];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	int t, n;
	int i, j;
	int times[102];
	int values[102];
	scanf("%d %d", &t, &n);
	for (i = 1; i <= n; i++) {
		scanf("%d %d", &times[i], &values[i]);
	}
	for (i = 1; i <= t; i++) {
		for (j = 1; j <= n; j++) {
			if (times[j] <= i)
				dp[i][j] = max(dp[i][j - 1], dp[i - times[j]][j - 1] + values[j]);
			else
				dp[i][j] = dp[i][j - 1];
		}
	}


	printf("%d", dp[t][n]);
	return 0;
}
