#include <stdio.h>

int score1[32];
int score2[32];
int time1[32];
int time2[32];

int dp1[1080002][32];

int max(int a, int b) {
	return a > b ? a : b;
}

int main( void ) {
	FILE* fin = fopen("TRUTH.INP", "r");
	FILE* fout = fopen("TRUTH.OUT", "w");
	int n, t;
	fscanf(fin, "%d %d", &n, &t);
	int i, j;
	for (i = 1; i <= n; i++) {
		fscanf(fin, "%d %d %d %d", &score1[i], &time1[i], &score2[i], &time2[i]);
	}
	for (i = 1; i <= t; i++) {
		for (j = 1; j <= n; j++) {
			if (time1[j] <= i) {
				dp1[i][j] = max(dp1[i][j - 1], dp1[i - time1[j]][j - 1] + score1[j]);
			} else {
				dp1[i][j] = dp1[i][j - 1];
			}
		}
	}
	int count = dp1[t][n];
	int tt = t;
	int temp = 0;
	for (i = n; i >= 1; i--) {
		if (time1[i] <= tt) {
			if (dp1[tt][n] == dp1[tt - time1[i]][i - 1] + score1[i]) {
				temp += time1[i];
				tt = tt - time1[i];
			}
		}
	}
	t -= temp;
	memset(dp1, 0, sizeof(dp1));
	for (i = 1; i <= t; i++) {
		for (j = 1; j <= n; j++) {
			if (time2[j] <= i) {
				dp1[i][j] = max(dp1[i][j - 1], dp1[i - time2[j]][j - 1] + score2[j]);
			} else {
				dp1[i][j] = dp1[i][j - 1];
			}
		}
	}
	fprintf(fout, "%d", dp1[t][n] + count);
	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}
