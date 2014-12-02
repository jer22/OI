#include <stdio.h>

int main( void ) {
	long n;
	scanf("%ld", &n);
	int i;
	long sum = 0;
	for (i = 0; sum < n; i++) {
		sum += i;
	}
	sum -= (i - 1);
	if (i % 2 == 1) printf("%d/%d", n - sum, i - (n - sum));
	else printf("%d/%d", i - (n - sum), n - sum);
	return 0;
}
