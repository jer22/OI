#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a < b ? a : b;
}

int main( void ) {
	FILE * in = fopen("bridge.in", "r");
	FILE * out = fopen("bridge.out", "w");
	int l, n;
	int i;
	int * arr;
	int max_re = 0;
	int min_re = 0;

	fscanf(in, "%d %d", &l, &n);
	arr = malloc((l + 1) * sizeof(int));
	for (i = 0; i < n; i++) {
		fscanf(in, "%d", &arr[i]);
	}
	
	for (i = 0; i < n; i++) {
		max_re = max(max(arr[i], (l - arr[i] + 1)), max_re);
		min_re = max(min(arr[i], (l - arr[i] + 1)), min_re);
	}

	fprintf(out, "%d %d", min_re, max_re);
	fclose(in);
	fclose(out);
	return 0;
}

