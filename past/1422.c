#include <stdio.h>

int main( void ) {
	int a;
	float re;
	scanf("%d", &a);
	if (a <= 150)
		re = a * 0.4463;
	else if (a <= 400)
		re = 150 * 0.4463 + (a - 150) * 0.4663;
	else re = 150 * 0.4463 + 250 * 0.4663 + (a - 400) * 0.5663;
	printf("%0.1f", re);
	system("pause");
	return 0;
}
