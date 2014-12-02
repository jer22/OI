#include <stdio.h>

int main ( void ) {
	FILE * in = fopen("bridge.in", "r");
	FILE * out = fopen("bridge.out", "w");
	int n;
	int sum = 0;
	int i;
	fscanf(in, "%d", &n);
	for (i = 1; i < n; i++) {
		sum += i;
	}
	if (n % 2 == 1) {
		sum /= n;
		sum *= ((n + 1) >> 1);
	} else {
		n -= 1;
		sum /= n;
		sum *= ((n + 1) >> 1);
	}
	fprintf(out, "%d", sum);

	fclose(out);
	fclose(in);
	return 0;
}

