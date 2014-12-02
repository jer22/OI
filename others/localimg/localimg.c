#include <stdio.h>

int arr[100002];
int count = 0;

void locate(int k) {
	if (arr[k]) {
		locate(k + 1);
		count++;
	}
	else
		arr[k] = 1;
}

int main( void ) {
	FILE* in = fopen("Localimg.in", "r");
	FILE* out = fopen("Localimg.out", "w");
	int n, k, t;
	fscanf(in, "%d%d%d", &n, &k, &t);
	int i, temp;
	for (i = 0; i < k; i++) {
		fscanf(in, "%d", &temp);
		locate(temp);
	}
	fprintf(out, "%d", count);
	fclose(in);
	fclose(out);
	return 0;
}
