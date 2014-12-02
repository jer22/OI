#include <stdio.h>

int arr[102][3];

int cmp(const void* a, const void* b) {
	return *(int *)b - *(int *)a;
}

int main( void ) {
	FILE* in = fopen("fall.in", "r");
	FILE* out = fopen("fall.out", "w");
	int x, y;
	int n;
	fscanf(in, "%d%d", &x, &y);
	fscanf(in, "%d", &n);
	int i;
	int count = y;
	for (i = 0; i < n; i++) {
		fscanf(in, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
	}
	qsort(arr, n, sizeof(arr[0]), cmp);
	for (i = 0; i < n; i++) {
		if (arr[i][0] > y)
			continue;
		if (x >= arr[i][1] && x <= arr[i][2]) {
			count += 5;
			x = arr[i][2];
			y = arr[i][0];
		}
	}
	fprintf(out, "%d", count);

	fclose(in);
	fclose(out);
	return 0;
}
