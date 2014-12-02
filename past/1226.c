#include <stdio.h>

void times(char *a, char *b) {
	int la = strlen(a);
	int lb = strlen(b);
	int l = la + lb - 2;
	int a1[1024];
	int b1[1024];
	int c[1024];
	int i, j;
	for (i = 0; i < la; i++)
		a1[i] = a[l - i - 1] - '0';
	for (i = 0; i < lb; i++)
		b1[i] = b[l - i - 1] - '0';
	for (i = 0; i < la; i++) {
		for (j = 0; j < lb; j++) {
			c[i + j] += a1[i] * b1[j];
		}
	}
	for (i = 0; i < l; i++) {
		if (c[i] > 9) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
	}
	for (i = l; i <= l; i++) {
		if (c[i] || c[i + 1]) l++;
	}
	memset(a, 0, sizeof(a));
	for (i = 0; i < l; i++) {
		a[l - i - 1] = a1[i] + '0';
	}
	a[i] = '\0';
	free(a1);
	free(b1);
	free(c);
}

int pow(long a, long b) {
	if(b == 0) return 1;
	long tp = pow(a, b >> 1);
	if(b & 1) return tp * tp * a;
	return tp * tp;
}

int main( void ) {
	long a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%ld", pow((a % c), b) % c);
	system("pause");
	return 0; 
}
