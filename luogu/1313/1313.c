#include <stdio.h>
#include <math.h>
#include <string.h>

#define MOD 10007

int arr[1002][1002];

long long power(int a, int b) {
	int i;
    long long r = 1;
	for (i = 0; i < b; i++) {
		r %= MOD;
		r *= a;
	}
	return r % MOD;
}

int main( void ) {
	int a, b, k, n, m;
	int i, j;
	memset(arr, 0, sizeof(arr));
	scanf("%d %d %d %d %d", &a, &b, &k, &n, &m);
	for (j = 1; j<= k; j++) {
		arr[j][1] = j;
		arr[j][j] = 1;
	}
	for (i = 2; i <= k; i++) {
		for (j = 2; j < k; j++) {
			arr[i][j] = (arr[i - 1][j - 1] + arr[i - 1][j]) % MOD;
		}
	}

	printf("%d", (arr[k][n] % MOD * power(a, n) % MOD * power(b, m) % MOD) % MOD);
	return 0;
}
