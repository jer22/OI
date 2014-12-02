#include <stdio.h>

int dp[30002][26];
int arr[26];
int value[26];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	int money, n;
	scanf("%d %d", &money, &n);
	int i, j;
	for (i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i], &value[i]);
		value[i] *= arr[i];
	}
	for (i = 1; i <= money; i++) {
		for (j = 1; j <= n; j++) {
			if  (i >= arr[j]) {
				dp[i][j] = max(dp[i][j - 1], dp[i - arr[j]][j - 1] + value[j]);
			} else {
				dp[i][j] = dp[i][j - 1];
			}
		}
	}

	printf("%d", dp[money][n]);
	system("pause");
	return 0;
}
