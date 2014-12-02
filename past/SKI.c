#include <stdio.h>
#include <stdlib.h>

int r,c;
int count = 1;
int ctemp = 1;
int arr[102][102];

void research(int i, int j) {
	if (ctemp > count)
		count = ctemp;
	int ii;
	if (j != 0 && arr[i][j - 1] < arr[i][j]) {
		ctemp ++;
		research(i, j - 1);
		ctemp --;
	} 
	if (i != r - 1 && arr[i + 1][j] < arr[i][j]) {
		ctemp ++;
		research(i + 1, j);
		ctemp --;
	} 	
	if (j != c - 1 && arr[i][j + 1] < arr[i][j]) {
		ctemp ++;
		research(i, j + 1);
		ctemp --;
	} 
	if (i != 0 && arr[i - 1][j] < arr[i][j]) {
		ctemp ++;
		research(i - 1, j);
		ctemp --;
	}
	return;
}

int main ( void ) {
	
	int i, j;
	FILE * in = fopen("SKI.in", "r");
	FILE * out = fopen("SKI.out", "w");
	fscanf(in, "%d %d", &r, &c);
	int temp = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			fscanf(in, "%d", &arr[i][j]);
		}
	}
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			research(i, j);
		}
	}
	
	fprintf(out, "%d", count);

	fclose(in);
	fclose(out);
	return 0;
}
