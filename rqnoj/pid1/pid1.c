#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int arr[102];
int main( void ) {
	int n;
	scanf("%d", &n);
	int count = n;
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(int), cmp);
	for (i = 1; i < n; i++) {
		if (arr[i] == arr[i - 1]) {
			count--;
			arr[i - 1] = 0;
		}
	}
	printf("%d\n", count);
	for (i = 0; i < n; i++) {
		if (arr[i])
			printf("%d ", arr[i]);
	}
	system("pause");
	return 0;
}
