#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int arr[1000004][2];

int cmp(const void *a, const void *b) {
	return *((int *)a + 1) - *((int *)b + 1);
}

int main( void ) {
	int n;
	int i;
	int start = 0;
	int count = 1;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = start; i < n; i++) {
		if (arr[i][0] >= arr[start][1]) {
			count ++;
			start = i;
		}
	}

	printf("%d", count);
	return 0;
}
