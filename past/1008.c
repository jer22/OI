#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	int i,j,k,n;
	int a[10];
	for(i = 123; i * 3 <= 987; i++) {
		k = 0;
		memset(a, 0, sizeof(a));
		a[i / 100] = 1;
		a[i / 10 % 10] = 1;
		a[i % 10] = 1;
		a[(i << 1) / 100] = 1;
		a[(i << 1) / 10 % 10] = 1;
		a[(i << 1) % 10] = 1;
		a[i * 3 / 100] = 1;
		a[i * 3 / 10 % 10] = 1;
		a[i * 3 % 10] = 1;
		for (j = 1; j < 10; j++)
			if (a[j] == 1) k++;
			if (k == 9) printf("%d %d %d\n", i, i << 1, i*3);
		}
	return 0;
}
