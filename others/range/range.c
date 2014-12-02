#include <stdio.h>

char arr[255][255];
int range[255][255];
int count[255];
int min(int a, int b, int c) {
	int r = a;
	if (r > b)
		r = b;
	if (r > c)
		r = c;
	return r;
}

int main( void ) {
	FILE *fin = fopen("range.in", "r");
	FILE *fout = fopen("range.out", "w");
	int n;
	fscanf(fin, "%d\n", &n);
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fin, "%c", &arr[i][j]);
		}
		fscanf(fin, "\n");
	}
	int num;
	for (i = 0; i < n; i++) {
		if (arr[0][i] == '1') {
			range[0][i] = 1;
		}
	}
	for (i = 0; i < n; i++) {
		if (arr[i][0] == '1') {
			range[i][0] = 1;
		}
	}
	for (i = 1; i < n; i++) {
		for (j = 1; j < n; j++) {
			if (arr[i][j] == '1') {
				range[i][j] = min(range[i][j - 1], range[i - 1][j], range[i - 1][j - 1]) + 1;
			}
		}
	}
	for (num = 2; num <= n; num++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (range[i][j] >= num) {
					count[num]++;
				}
			}
		}
	}
	for (i = 2; i <= n; i++) {
		if (count[i]) {
			fprintf(fout, "%d %d\n", i, count[i]);
		}
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
