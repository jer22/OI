#include <stdio.h>
#include <stdlib.h>

long arr[1000002];
long len[1000002];
int cmp(const void *a, const void *b) {
	return *(int *)b - *(int *)a;
}

int eq(long *a, long n) {
	int maxlen = 0;
	int i, j;
	memset(len, 0, sizeof(len));
	for (i = 1; i < n; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (a[j] == a[i] && len[j] > len[i])
				len[i] = len[j];
		}
		len[i]++;
		if (len[i] > maxlen)
			maxlen = len[i];
	}
	return maxlen;
}

int main( void ) {
	FILE * in = fopen("leader2.in", "r");
	FILE * out = fopen("leader2.out", "w");
	long n, k;
	long count = 0;
	int i;
	fscanf(in, "%ld %d", &n, &k);
	for (i = 0; i < k; i++) {
		fscanf(in, "%ld", &arr[i]);
	}
	qsort(arr, k, sizeof(arr[0]), cmp);
	int maxl = eq(arr, k);
	long temp = arr[0];
	for (i = 0; i < k; i++) {
		if (arr[i] == temp) {
			count ++;
			if (arr[i] == arr[0]) {
				if (count == (maxl + 1) && count > (k >> 1)) {
					fprintf(out, "%d", arr[i]);
					fclose(in);
					fclose(out);
					exit(0);
				}
			} else {
				if (count == maxl && count > (k >> 1)) {
					fprintf(out, "%d", arr[i]);
					fclose(in);
					fclose(out);
					exit(0);
				}
			}
			
		} else {
			temp = arr[i];
			count = 1;
		}
	}
	fprintf(out, "-1");
	fclose(in);
	fclose(out);
	return 0;
}
