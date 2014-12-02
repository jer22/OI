#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	int n;
	scanf("%d", &n);
	int i;
	int arr[102];
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	int temp = arr[0];
	int count = n;
	for (i = 1; i < n; i++) {
		if (arr[i] == temp) {
			arr[i] = -1;
			count --;
		} else temp = arr[i];
	}
	printf("%d\n", count);
	for (i = 0; i < n; i++) {
		if (arr[i] == -1) continue;
		printf("%d ", arr[i]);
	}

	return 0;
}
