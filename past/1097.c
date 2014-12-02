#include <stdio.h>
#include <stdlib.h>

long arr[10002];

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	int count = 0;
	long temp = arr[0];
	for (i = 0; i < n; i++) {
		if (arr[i] == temp) {
			count ++;
		} else {
			printf("%ld %d\n", arr[i - 1], count);
			system("pause");
			temp = arr[i];
			count = 1;
		}
	}
	printf("%ld %d\n", arr[i - 1], count);
	system("pause");
	return 0;
}
