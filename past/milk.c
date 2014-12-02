#include <stdio.h>
#include <stdlib.h>

int cmp( const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	FILE * in = fopen("milk.in", "r");
	FILE * out = fopen("milk.out", "w");
	int m, n;
	int arr[5002][2];
	fscanf(in, "%d %d", &m, &n);
	int i, j;
	int sum = 0, cost = 0;
	for (i = 0; i < n; i++) {
		fscanf(in, "%d %d", &arr[i][0], &arr[i][1]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		for (j = 1; j <= arr[i][1]; j++) {
			if (sum < m) {
				cost += arr[i][0];
				sum ++;
			} else {
				fprintf(out, "%d", cost);
				fclose(in);
				fclose(out);
				exit(0);
			}
		}
	}
	fprintf(out, "%d", cost);
	fclose(in);
	fclose(out);
	return 0;
}
