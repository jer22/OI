#include <stdio.h>
#include <stdlib.h>

int arr[10002];

int cmp( const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

void insertSort(int *a, int n) {
	int i, j;
	int temp;
	for (i = 1; i < n; i++) {
		temp = a[i];
		for(j = i - 1; j >= 0 && temp < a[j]; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}

int main( void ) {
	int m, n;
	scanf("%d %d", &n, &m);
	int i;
	int start = 0;
	int end = m;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	if (m >= n) {
		qsort(arr, n, sizeof(arr[0]), cmp);
		printf("%d", arr[n - 1]);
		exit(0);
	}
	qsort(arr, m, sizeof(arr[0]), cmp);
	while (arr[n - m - 1]) {
		arr[start++] += arr[end];
		arr[end++] = 0;
		insertSort(arr, end);
	}
	printf("%d", arr[n - 1]);


	system("pause");
	return 0;
}
