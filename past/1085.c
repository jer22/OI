#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	int arr[8][2];
	int i;
	int sum, max = 0;
	memset(arr, 0, sizeof(arr));
	for (i = 1; i < 8; i++) {
		scanf("%d %d", &arr[i][0], &arr[i][1]);
	}
	for (i = 1; i < 8; i++) {
		sum = arr[i][0] + arr[i][1];
		if (sum > 8) {
			if (sum > (arr[max][0] + arr[max][1]))
				max = i;
		}
	}
	printf("%d", max);

	system("pause");
	return 0;
}
