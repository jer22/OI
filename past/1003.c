#include <stdio.h>

long x, y;

int onCarpet(long a, long b, long w, long h) {
	return (x >= a && x <= (w + a) && y >= b && y <= (h + b));
}

int main( void ) {
	int n;
	scanf("%d\n", &n);
	
	long arr[10005][4];
	long i;
	for (i = 0; i < n; i++) {
		scanf("%d %d %d %d\n",
			&arr[i][0], &arr[i][1], &arr[i][2], &arr[i][3]);
	}
	scanf("%d %d", &x, &y);

	for (i = n - 1; i >= 0; i--) {
		if (onCarpet(arr[i][0], arr[i][1], arr[i][2], arr[i][3])) {
			printf("%d", i + 1);
			exit(0);
		}
	}
	printf("-1");



	return 0;
}
