#include <stdio.h>
#include <string.h>
#include <math.h>

long a, b;
FILE * in;
FILE * out;
long arr[1024];
int n = 0;

int cmp(const void *p, const void *q) {
	return *(long *)p - *(long *)q;
}

void print(long pal) {
	int m;
	long sq;
	if (pal >= a && pal <= b) {
		sq = sqrt(pal);
		for (m = 2; m < sq; m++) {
			if (pal % m == 0) {
				break;
			}
		}
		if (pal % m != 0) {
			arr[n++] = pal;
		}
	}
}

int main( void ) {
	in = fopen("pprime.in", "r");
	out = fopen("pprime.out", "w");
	int i, j, k, l;
	scanf("%ld %ld", &a, &b);
	long pal, sq;
	if (a == 5) arr[n++] = 5;
	if (a <= 7) arr[n++] = 7;
	if (a <= 11) arr[n++] = 11;

	for (i = 1; i <= 9; i += 2) {
		for (j = 0; j <= 9; j++) {
			pal = 100 * i + 10 * j + i;
			print(pal);
			pal = 1000 * i + 100 * j + 10 * j + i;
			print(pal);
			for (k = 0; k <= 9; k++) {
				pal = 10000 * i + 1000 * j + 100 * k + 10 * j + i;
				print(pal);
				pal = 100000 * i + 10000 * j + 1000 * k + 100 * k + 10 * j + i;
				print(pal);
				for (l = 0; l <= 9; l++) {
					pal = 1000000 * i + 100000 * j + 10000 * k + 1000 * l + 100 * k + 10 * j + i;
					print(pal);
				}
			}
			
		}
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		printf("%ld\n", arr[i]);
	}
	return 0;
}
