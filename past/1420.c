#include <stdio.h>

int main( void ) {
	int n;
	scanf("%d", &n);
	int i;
	int count = 1, max = 0;
	int arr[10002];
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (i = 1; i < n; i++) {
		if (arr[i] - arr[i - 1] == 1)
			count ++;
		else
			count = 1;
		if (count > max)
			max = count;
	}
	printf("%d", max);
	system("pause");
	return 0;
}
