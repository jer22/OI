#include <iostream>

using namespace std;

float arr[200000];
int main( void ) {
	FILE* fin = fopen("Maximum.in", "r");
	FILE* fout = fopen("Maximum.out", "w");
	long n;
	fscanf(fin, "%ld", &n);
	long i;
	for (i = 0; i < n; i++) {
		fscanf(fin, "%f", &arr[i]);
	}
	sort(arr, arr + n);
	for (i = 0; i < n - 1; i++) {
		arr[i] = arr[i + 1] - arr[i];
	}
	arr[n - 1] = 0.0f;
	sort(arr, arr + n - 1);
	float re = arr[n - 1];
	int integer = (int)re;
	int s[6] = {0, 0, 0, 0, 0, 0};
	for (i = 0; i < 6; i++) {
		re *= 10;
		s[i] = (int)re % 10;
	}
	fprintf(fout, "%d.", integer);
	for (i = 5; i >= 0; i--) {
		if (s[i])
			break;
	}
	n = i + 1;
	for (i = 0; i < n; i++) {
		fprintf(fout, "%d", s[i]);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
