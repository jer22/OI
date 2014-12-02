#include <stdio.h>
#include <stdlib.h>

int main( void ) {
	FILE * in = fopen("NewStart.in", "r");
	FILE * out = fopen("NewStart.out", "w");
	int i, j, k;
	int n;
	int * cost;
	int ** p;
	fscanf(in, "%d", &n);
	cost = malloc(n * sizeof(int));
	p = malloc((n + 1) * sizeof(int *));
	for (i = 0; i < n + 1; i++) {
		p[i] = malloc((n + 1) * sizeof(int));
	}
	for (i = 0; i < n; i++) {
		fscanf(in, "%d", &cost[i]);
	}
	p[0][0] = 0;
	for (i = 1; i < n + 1; i++) {
		p[0][i] = cost[i - 1];
	}
	for (i = 1; i < n + 1; i++) {
		
		for (j = 1; j < n + 1; j++) {
			fscanf(in, "%d", &p[i][j]);
			
		}
		p[i][0] = cost[i - 1];
	}

	for (i = 0; i < n + 1; i++) {
		for (j = 0; j < n + 1; j++) {
			printf("%d", p[i][j]);
		}
		printf("\n");
	}







	system("pause");

	for (i = 0; i < n; i++) {
		free(p[i]);
	}
	free(p);
	free(cost);
	fclose(in);
	fclose(out);
	return 0;
}
