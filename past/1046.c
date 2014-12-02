#include <stdio.h>

int main( void ) {
	int arr[10];
	int i;
	int hei;
	int count = 0;
	for (i = 0; i < 10; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d", &hei);
	hei += 30;
	for (i = 0; i < 10; i++)
		if (hei >= arr[i])
			count++;
	printf("%d", count);
	system("pause");
	return 0;
}
