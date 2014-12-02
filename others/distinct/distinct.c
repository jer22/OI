#include <stdio.h>

int x[1000000];
int y[1000000];
int main( void ) {
	FILE* fin = fopen("distinct.in", "r");
	FILE* fout = fopen("distinct.out", "w");
	int n;
	int ax, bx, cx, ay, by, cy;
	fscanf(fin, "%d%d%d%d%d%d%d%d%d", &n, &x[1], &ax, &bx, &cx,
		&y[1], &ay, &by, &cy);
	int i, j;
	for (i = 1; i <= n; i++) {
		x[i + 1] = (x[i] * ax + bx + i) % cx;
		y[i + 1] = (y[i] * ay + by + i) % cy;
		printf("%d %d\n", x[i], y[i]);
	}

	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}
