#include <stdio.h>
#include <math.h>

int x[1002];
int y[1002];
int hash[1010];
int len[1010];
int xx[1010];
int yy[1010];
int count = 0;

int main( void ) {
	FILE* in = fopen("Allbarns.in", "r");
	FILE* out = fopen("Allbarns.out", "w");
	int n;
	int i, j;
	int a, b, l, h;
	fscanf(in, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(in, "%d %d", &x[i], &y[i]);
		for (j = 0; j < i; j++) {
			a = x[i] + x[j];
			b = y[i] + y[j];
			l = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
			h = (abs(a * 1343 + b * 3217 + l * 1321)) % 1009;
			while (hash[h] && (len[h] != l || xx[h] != a || yy[h] != b)) {
				h = (h + 1307) % 1009;
			}
			if (!hash[h]) {
				xx[h] = a;
				yy[h] = b;
				len[h] = l;
				hash[h] = 1;
			} else {
				count += hash[h];
				hash[h]++;
			}
		}
		fprintf(out, "%d\n", count);
	}
	fclose(in);
	fclose(out);
	return 0;
}
