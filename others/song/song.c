#include <stdio.h>

int arr[64];
int dp[1002][64];

int n, begin, m;

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	FILE* in = fopen("song.in", "r");
	FILE* out = fopen("song.out", "w");
	
	fscanf(in, "%d%d%d", &n, &begin, &m);
	n -= 1;
	int i, j;
	for (i = 1; i <= n; i++) {
		fscanf(in, "%d", &arr[i]);
	}
	if (begin + arr[1] > m && begin - arr[1] < 0) {
		fprintf(out, "-1");
		fclose(in);
		fclose(out);
		exit(0);
	}
	for (i = 0; i <= m; i++) {
		dp[i][0] = begin;
	}
	for (i = 0; i <= n; i++) {
		dp[0][i] = begin;
	}
	for (i = 1; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			if (i >= arr[j]) {
				if (dp[i - arr[i]][j - 1] + arr[i] > m && dp[i][j - 1] - arr[i] >= 0) {
					dp[i][j] = dp[i][j - 1] - arr[i];
				} else if (dp[i - arr[i]][j - 1] + arr[i] <= m && dp[i][j - 1] - arr[i] < 0) {
					dp[i][j] = dp[i - arr[i]][j - 1] + arr[i];
				} else if (dp[i - arr[i]][j - 1] + arr[i] < m && dp[i][j - 1] - arr[i] >= 0) {
					dp[i][j] = max(dp[i - arr[i]][j - 1] + arr[i], dp[i][j - 1] - arr[i]);
				} else {
					dp[i][i] = -1;
				}
			} else {
				dp[i][j] = -1;
			}
		}
	}

	for (i = 0; i <= m; i++) {
		for (j = 0; j <= n; j++) {
			printf("%d ", dp[i][j]);
		}
		printf("\n");
	}

	printf("%d", dp[m][n]);
	system("pause");
	fclose(in);
	fclose(out);
	return 0;
}
