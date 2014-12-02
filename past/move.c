#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	FILE * in = fopen("move.in", "r");
	FILE * out = fopen("move.out", "w");
	int n;
	int * arr;
	int i;
	fscanf(in, "%d", &n);
	arr = malloc(n * sizeof(int));
	for(i = 0; i < n; i++) {
		fscanf(in, "%d", &arr[i]);
	}

	free(arr);
	fclose(in);
	fclose(out);
	return 0;
}
