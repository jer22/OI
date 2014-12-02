#include <stdio.h>
#include <string.h>

int n;

int dp(int i) {
	if (!i) 		return n;
	if (i == n + 1) return 1;
	return i;
}

int main( void ) {
	int m;
	int arr[40][40] ;
	int i, j;
	memset(arr, 0, sizeof(arr));
	scanf("%d %d", &n, &m);
	arr[1][1] = 1;
	arr[1][n - 1] = 1;
	for (i = 2; i <= m; i++) {
		for (j = 1; j <= n; j++) {
			arr[i][j] = arr[i - 1][dp(j - 1)] + arr[i - 1][dp(j + 1)]; 
		}
	}
	printf("%d", arr[m][n]);
	
	return 0;  
}