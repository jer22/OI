#include <stdio.h>

int main( void ) {
	int i;
	int now;
	int save = 0;
	int over = 0;
	int temp;
	for (i = 0; i < 12; i++) {
		scanf("%d", &now);
		temp = 300 + over - now;
		over = temp % 100;
		save += temp - over;
		if (temp < 0) {
			printf("-%d\n", i + 1);
			exit(0);
		}
	}
	printf("%d", over + (save * 6 / 5));
	return 0;
}
