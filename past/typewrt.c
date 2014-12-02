#include <stdio.h>
#include <string.h>

int a1[10024];
int b1[10024];
void add(char * a, char * b) {
	int la = strlen(a), lb = strlen(b);
	int l = la > lb ? la : lb;
	memset(a1, 0, sizeof(a1));
	memset(b1, 0, sizeof(b1));
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
	memset(a, 0, sizeof(a));
	for (i = 0; i < l; i++) {
		a[l - i - 1] = a1[i] + '0';
	}
	a[i] = '\0';
}

int a2[10024];
int c[10024];
void times(char * a, int b) {
	int l = strlen(a);
	memset(a1, 0, sizeof(a1));
	memset(c, 0, sizeof(c));
	int i, j;
	
	for (i = l - 1; i >= 0; i--) {
		a1[l - i - 1] = a[i] - '0'; 
	}
	for (i = 0; i < l; i++) {
		c[i] += (a1[i] * b);
	}
	for (i = 0; i <= l; i++) {
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
		a[i] = c[l - i - 1] + '0';
	}

	a[i] = '\0';
}

char a[10024];
char * power(int b) {
	memset(a, 0, sizeof(a));
	a[0] = '1';
	a[1] = '\0';
	if (!b)
		return a;
	int i;
	for (i = 1; i <= b; i++) {
		times(a, 9);
    }
    return (a);
}

int main( void ) {
	FILE * in = fopen("typewrt.in", "r");
	FILE * out = fopen("typewrt.out", "w");
	int n;
	fscanf(in, "%d", &n);
	int i, j;
	char sum[10024];
	char temp[10024];
	strcpy(sum, "0");
	strcpy (temp, "1");
	for (i = 1; i <= n; i++) {
		times(sum, 10);
		add(sum, temp);
		times(temp, 9);
	}
	fprintf(out, "%s", sum);
	fclose(in);
	fclose(out);
	return 0;
}
