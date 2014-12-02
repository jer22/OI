#include <stdio.h>
#include <string.h>

void div(char *a, long b) {
	int a1[10024];
	int c[10024];
	int l = strlen(a);
	int i, j = 0;
	for (i = 0; i < l; i++)
		a1[i] = a[i] - '0';
	for (i = 0; i < l; i++) {
		c[i] = a1[i] / b;
		a1[i + 1] += (a1[i] % b) * 10;
	}
	memset(a, 0, sizeof(a));
	while (!c[j++]);
	l -= (j - 1);
	for (i = 0; i < l; i++) {
		a[i] = c[i + j - 1] + '0';
	}
	a[l] = '\0';
}

int main( void ) {
	char a[10024];
	long b;
	scanf("%s %ld", a, &b);
	div(a, b);
	printf("%s", a);




	system("pause");
	return 0;
}
