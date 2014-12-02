#include <stdio.h>
#include <stdlib.h>

int arr[100002];

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	int n;
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
