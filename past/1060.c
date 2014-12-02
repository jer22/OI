#include <stdio.h>
#include <string.h>

int max(int a, int b) {
	return a > b ? a : b;
}

int value[26];
int arr[26];
int dp[50002][26];
int main( void ) {
	int n, m;
	scanf("%d %d", &m, &n);
	int i, j;
	int a, b;
	for (i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		arr[i] = a;
		value[i] = a * b;
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (arr[j] <= i)
				dp[i][j] = max(dp[i][j - 1], dp[i - arr[j]][j - 1] + value[j]);
			else 
				dp[i][j] = dp[i][j - 1];
		}
	}
	printf("%d", dp[m][n]);
	system("pause");
	return 0;
}
