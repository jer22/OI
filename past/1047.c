#include <stdio.h>

int main( void ) {
	int l, n;
	int arr[10002];
	int a, b;
	int count = 0;
	scanf("%d %d", &l, &n);
	memset(arr, 0, sizeof(arr));
	int i, j;
	for (i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		for (j = a; j <= b; j++) {
			arr[j] = 1;
		}
	}
	for (i = 0; i <= l; i++) {
		if (arr[i])
			count ++;
	}
	printf("%d", (l - count + 1));

	system("pause");
	return 0;
}
