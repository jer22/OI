#include <stdio.h>
#include <stdlib.h>

int * cmp(const void *a, const void * b) {
	return *(int *)a - *(int *)b;
}

int n;
long k;
int arr[102];
long re[200005];
int main( void ) {
	FILE * in = fopen("Panda.in", "r");
	FILE * out = fopen("Panda.out", "w");
	long i;
	fscanf(in, "%d %ld", &n, &k);
	for (i = 0; i < n; i++) {
		fscanf(in, "%d", &arr[i]);
	}
	long j;
	for (i = 0; i < n; i++) {
		re[i] = arr[i];
	}
	long idx = n;

	for (i = 0; i < (k << 1); i++) {
		for (j = (long)(i % n); j < n; j++) {
			re[idx++] = arr[j] * re[i];
		}	
	}
	qsort(re, (k << 1), sizeof(int), cmp);
	fprintf(out, "%ld", re[k - 1]);


	fclose(in);
	fclose(out);
	return 0;
}
