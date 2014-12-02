#include <stdio.h>

int main( void ) {
	float k;
	float sum = 0;
	float i;
	scanf("%f", &k);
	for (i = 1; sum <= k; i++) {
		sum += 1 / i;
	}

	printf("%0.0f", --i);

	return 0;
}
