#include <stdio.h>
#include <string.h>

int main( void ) {
	int n;
	scanf("%d", &n);
	int arr[1002];
	memset(arr, 0, sizeof(arr));
	int i, j;
	for (i = 1; i <= (n >> 1); i++) {
		for (j = 1; j <= (i >> 1); j++)
			arr[i] += arr[j];
		arr[i]++;
	}
	for (i = 1; i <= (n >> 1); i++)
		arr[n] += arr[i];
	arr[n] ++;
	printf("%d", arr[n]);
	return 0;
}
