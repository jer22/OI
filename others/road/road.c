#include <stdio.h>

int arr[2000][3];
int main( void ) {
	FILE* fin = fopen("road.in", "r");
	FILE* fout = fopen("road.out", "w");
	int n, m;
	fscanf(fin, "%d %d", &n, &m);
	int i;
	for (i = 0; i < m; i++)
		fscanf("%d %d %d", &arr[i][0], &arr[i][1]; &arr[i][2]);

	for (i = 0; i < m; i++) {
		if (i < n - 2) {
			printf("0\n");
			continue;
		}

	}


	fclose(fin);
	fclose(fout);
	system("pause");
	return 0;
}
