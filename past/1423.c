#include <stdio.h>

int main( void ) {
	float x;
	scanf("%f", &x);
	int i = 0;
	float v = 0;
	float now = 2;
	while (v < x) {
		v += now;
		now *= 0.98;
		i++;
	}
	printf("%d", i);
	system("pause");
	return 0;
}
