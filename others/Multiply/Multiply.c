#include <stdio.h>
#include <string.h>

char a[10000], b[10000];

void times(char* a, char* b) {
	int a1[10000], b1[10000], c[10000];
	int i, j, m, l1, l2;
	l1 = strlen(a);
	l2 = strlen(b);
	m = l1 + l2 - 2;
	for(i = 0; i < l1; i++)
		a1[i] = a[l1 - i - 1] - '0';
	for(i = 0; i < l2; i++)
		b1[i] = b[l2 - i - 1] - '0';
	for(i = 0; i < l1 ;i++)
		for(j = 0; j < l2; j++)
			c[i + j] += (a1[i] * b1[j]);
	for(i = 0; c[i]; i++) {
		if(c[i] > 9) {
			c[i + 1] += c[i] / 10;
			c[i] = c[i] % 10;
		}
		if(c[m]) m++;
	}
	memset(a, 0, sizeof(a));
	for(i = 0; i < m; i++)
		a[i] = c[m - i - 1] + '0';
	a[m] = '\0';
}

int main(void) {
	FILE* in = fopen("Multiply.in", "r");
	FILE* out = fopen("Multiply.out", "w");
	int m,n,i,j;
	fscanf(in, "%s%s", a, b);
	times(a,b);
	fprintf(out, "%s",a);
	fclose(in);
	fclose(out);
	return 0;
}  

