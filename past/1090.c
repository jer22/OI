#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

void insertSort(int *a, int n) {
	int i, j;
	int temp;
	for (i = 1; i < n; i++) {
		temp = a[i];
		for (j = i; j > 0 && temp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = temp;
	}
}

int main( void ) {
	int n;
	int i, j;
	int arr[10002];
	int sum[10002];
	memset(sum, 0, sizeof(sum));
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n + 1, sizeof(arr[0]), cmp);
	for (i = 1; i < n; i++) {
		insertSort(arr, n + 1);
		arr[i + 1] += arr[i];
		arr[i] = 0;
		sum[i] = arr[i + 1];
	}

	for (i = 1; i < n; i++) {
		sum[n] += sum[i];
	}
	printf("%d", sum[n]);
	system("pause");
	return 0;
}
