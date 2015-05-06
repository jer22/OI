#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

int arr[1005][1005];
long long sum[1005][1005];
int main() {
	freopen("i.in", "r", stdin);
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= 1000; j++) {
			int t = gcd(i, j);
			arr[i][j] = (i + j) / t;
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (long long)arr[i][j];
		}
	}
	int n, m;
	while (~scanf("%d %d", &n, &m)) {
		printf("%lld\n", sum[n][m]);
	}

	return 0;
}
