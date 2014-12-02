#include <stdio.h>

int I = 0, V = 0, X = 0, L = 0, C = 0, D = 0, M = 0;
int map[5]={0,1,2,3,1};

int main( void ) {
	FILE * in = fopen("preface.in", "r");
	FILE * out = fopen("preface.out", "w");
	int n;
	fscanf(in, "%d", &n);
	int i;
	int a, b, c, d;
	for (i = 1; i <= n; i++) {
		a = i % 10;
		b = i / 10 % 10;
		c = i / 100 % 10;
		d = i / 1000;
		I += map[a % 5];
		if (a >= 4 && a <= 8) V++;
		else if (a == 9) X++;
		X += map[b % 5];
		if (b >= 4 && b <= 8) L++;
		else if (b == 9) C++;
		C += map[c % 5];
		if (c >= 4 && c <= 8) D++;
		else if (c == 9) M++;
		M += map[d % 5];
	}
	if (I) fprintf(out, "I %d\n", I);
	if (V) fprintf(out, "V %d\n", V);
	if (X) fprintf(out, "X %d\n", X);
	if (L) fprintf(out, "L %d\n", L);
	if (C) fprintf(out, "C %d\n", C);
	if (D) fprintf(out, "D %d\n", D);
	if (M) fprintf(out, "M %d\n", M);
	fclose(in);
	fclose(out);
	return 0;
}
