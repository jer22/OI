#include <stdio.h>

long arr[100002];
int main( void ) {
	int n, k;
	scanf("%d %d", &n, &k);
	int i, j;
	arr[1] = 1;
	for (i = 2; i <= k; i++) {
		for (j = 1; j < i; j++) {
			arr[i] += arr[j];
		}
		arr[i]++;
		printf("%ld\n", arr[i]);
	}
	for (i = k + 1; i <= n; i++) {
		for (j = i - k; j < i; j++)
			arr[i] += arr[j];
	}
	printf("%ld", arr[n] % 100003);
	system("pause");
	return 0;
}
