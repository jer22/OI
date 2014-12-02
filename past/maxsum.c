#include <stdio.h>
#include <stdlib.h>

int dp[1000][1000];

int max(int a, int b) {
	return a > b ? a : b;
}

int maxsum(int a) {
	int i;
	int sum = 0;
	for (i = 1; i < a; i++)
		if (!(a % i))
			sum += i;
	return sum;
}

int main( void ) {
	FILE * in = fopen("maxsum.in", "r");
	FILE * out = fopen("maxsum.out", "w");
	int arr[1000];
	int sum;
	fscanf(in, "%d", &sum);
	int i, j;
	for (i = 0; i <= sum; i++) {
		arr[i] = maxsum(i);
	}
	for (i = 1; i <= sum; i++) {
		for (j = 1; j <= sum; j++) {
			if (j <= i) {
				dp[i][j] = max(dp[i][j - 1], dp[i - j][j - 1] + arr[j]);
			} else {
				dp[i][j] = dp[i][j - 1];
			}
		}
	}
	fprintf(out, "%d", dp[sum][sum]);
	fclose(in);
	fclose(out);
	return 0;
}
