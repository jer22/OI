#include <stdio.h>

int arr[256];
int re[256];

int cmp(const void *a, const void *b) {
	return *(int *)b - *(int *)a;
}

int cmp1(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	FILE * fin = fopen("barn1.in", "r");
	FILE * fout = fopen("barn1.out", "w");
	int n, m, s;
	fscanf(fin, "%d %d %d", &m, &s, &n);
	int i, j;
	int temp = 0;
	int count = 0;
	for (i = 0; i < n; i++) {
		fscanf(fin, "%d", &arr[i]);
	}
	qsort(arr, n, sizeof(int), cmp1);
	for (i = 0; i < n - 1; i++) {
		re[i] = arr[i + 1] - arr[i];
	}
	for (i = 0; i < n - 1; i++) {
		if (re[i] != 1 && re[i]) {
			temp ++;
		}
	}
	re[n - 1] = 1;
	qsort(re, n, sizeof(int), cmp);
	if (temp < m) {
		fprintf(fout, "%d", n);
		exit(0);
	}
	for (i = m - 1; i < n; i++) {
		count += re[i];
	}
	count += (m - 1);
	fprintf(fout, "%d", count);
	return 0;
}
