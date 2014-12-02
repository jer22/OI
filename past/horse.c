#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int main( void ) {
	int tianji[5002];
	int qiwei[5002];
	FILE * in = fopen("horse.in", "r");
	FILE * out = fopen("horse.out", "w");
	int n;
	int i, j;
	int count = 0;
	fscanf(in, "%d", &n);
	for (i = 0; i < n; i++)
		fscanf(in, "%d", &qiwei[i]);
	for (i = 0; i < n; i++)
		fscanf(in, "%d", &tianji[i]);
	qsort(tianji, n, sizeof(tianji[0]), cmp);
	qsort(qiwei, n, sizeof(qiwei[0]), cmp);
	for (i = n - 1; i >= 0; i--) {
		for (j = 0; j < n; j++)
			if (tianji[i] <= qiwei[j])
				break;
		if (j == 0)
			count--;
		else {
			count++;
			qiwei[j - 1] = 501;
		}
	}

	printf("%d", count);
	fclose(in);
	fclose(out);
	system("pause");
	return 0;
}
