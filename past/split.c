#include <stdio.h>
#include <math.h>

int main( void ) {
	FILE * in = fopen("split.in", "r");
	FILE * out = fopen("split.out", "w");
	long long n;
	long sum = 0;
	long long i;
	fscanf(in, "%lld", &n);


	/*for (i = 1; i <= ((n + 1) >> 1); i++) {

		if (i % 2 == 0) {
			if ((n / i) * i + (i >> 1) == n) {
				/*printf("%d %d %d\n", i, (n % i), (n / i) * i);*/
				sum ++;
			}
			/*if (n % i == (i >> 1)) {
				printf("%d %d %d\n", i, (n % i), (n / i) * i);
				sum ++;
			}*/
		/*} else {
			if (n % i == 0) {
				/*printf("%d %d %d\n", i, (n % i), (n / i) * i);*/
	/*			sum ++;
			}
		}
	}
	
	/*system("pause");*/
	
	fprintf(out, "%d", sum);
	fclose(in);
	fclose(out);
	return 0;
}


