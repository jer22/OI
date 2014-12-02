#include <stdio.h>
#include <stdlib.h>

long * arr;
int count;

void find(long n, long * arr) {
	if (n == 1) {
		return;
	}
	long i, j = 0;
	
	long k = (n >> 1);
	for (i = 1; i <= k; i++) {
		if ((n % i) == 0) {
			arr[j++] = (n / i);
		}
	}
	arr[j++] = 1;
	for (i = 0; i < j; i++) {
		printf("%d ", arr[i]);
	}
	for (i = 0; i < j; i++) {
		count ++;
		find(arr[i], malloc(n * sizeof(int)));
		count --;
	}
	return;

}

int main( void ) {
	FILE * in = fopen("enb.in", "r");

	long n;
	long en;
	
	
	long temp;

	while(fscanf(in, "%ld", &n) != EOF) {

		find(n, malloc(n * sizeof(int)));

		free(arr);
	}




	system("pause");
	return 0;
}


