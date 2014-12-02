#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * add(char * a, char * b) {
    
	int la = strlen(a), lb = strlen(b);
	int l = la > lb ? la : lb;
	int * a1 = calloc(l + 2, sizeof(int));
	int * b1 = calloc(l + 2, sizeof(int));
	char * c = calloc(l + 2, sizeof(char));
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
	free(a1);
	free(b1);
	return c;
}

char arr[5010][10005] = {0};
int main( void ) {
	int n;
	scanf("%d", &n);
	int i;
	strcpy(arr[0], "0");
	strcpy(arr[1], "1");
	strcpy(arr[2], "2");
	for (i = 3; i <= n; i++) {
		strcpy(arr[i], add(arr[i - 1], arr[i - 2]));
	}
	printf("%s", arr[n]);
	return 0;
}
