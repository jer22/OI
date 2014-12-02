#include <stdio.h>

int arr[1002];
int main( void ) {
	FILE* fin = fopen("Half.in", "r");
	FILE* fout = fopen("Half.out", "w");
	int n;
	fscanf(fin, "%d", &n);
	int i, j;
	int re = 1;
	for (i = 1; i <= n >> 1; i++) {
		for (j = 0; j <= i >> 1; j++) {
			arr[i] += arr[j];
		}
		arr[i]++;
		printf("%d\n", arr[i]);
		re += arr[i];
	}

	fprintf(fout, "%d", re);
	fclose(fin);
	fclose(fout);
	return 0;
}
