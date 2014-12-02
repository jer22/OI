#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int r[10000];

int mod(char a[], int l, int b) {
	int i, j;
	for (i = 0; i < l; i++) {
		r[i] = a[i] - '0';
	}
	for (i = 0; i <= l; i++) {
		r[i + 1] += r[i] % b * 10;
	}
	return r[l + 1];
}

int main( void ) {
	char a[10002];
	int re;
	int n;
	char ch;
	int len = 0;
	FILE * in = fopen("YUBIKILI.in", "r");
	FILE * out = fopen("YUBIKILI.out", "w");
	int i = 0;
	fscanf(in, "%d", &n);
	fscanf(in, "%s", a);
	len = strlen(a);

	re = mod(a, len, n);
	if (re == 0) fprintf(out, "%d", n);
    else fprintf(out, "%d", re % n);

	fclose(in);
	fclose(out);
	return 0;
}


