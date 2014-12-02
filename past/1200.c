#include <stdio.h>
#include <string.h>

int main( void ) {
	char ufo[8];
	char gro[8];
	scanf("%s %s", ufo, &gro);
	int i;
	int r1 = 1, r2 = 1;
	int lu = strlen(ufo);
	int lg = strlen(gro);
	for (i = 0; i < lu; i++)
		r1 *= (int)ufo[i] - 64;
	for (i = 0; i < lg; i++)
		r2 *= (int)gro[i] - 64;
	if (r1 % 47 == r2 % 47)
		printf("GO");
	else printf("STAY");

	system("pause");
	return 0;
}
