#include <stdio.h>
#include <string.h>

char * add(char * a, char * b) {
	int la = strlen(a), lb = strlen(b);
	int l = la > lb ? la : lb;
	int a1[1002];
	int b1[1002];
	char c[1002];
	int i;
	
	for (i = la - 1; i >= 0; i--)
		a1[la - i - 1] = a[i] - '0';
	for (i = lb - 1; i >= 0; i--)
		b1[lb - i - 1] = b[i] - '0';
	for (i = 0; i < l; i++) {
		a1[i] += b1[i];
		a1[i + 1] += a1[i] / 10;
		a1[i] = a1[i] % 10;
	}
	if (a1[l]) l++;
	for (i = 0; i < l; i++) {
		c[l - i - 1] = a1[i] + '0';
	}
	c[i] = '\0';
	return c;
}

int main( void ) {
	char a[512];
	char b[512];
	scanf("%s %s", &a, &b);
	int i;
	char * re = add(a, b);
	printf("%s", re);
	system("pause");
	return 0;
}
