#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 505;

int MOD;
struct matrix{
	int n, m;
	int arr[MAXN][MAXN];
	matrix(int i, int j) : n(i), m(j) {
		memset(arr, 0, sizeof(arr));
	}
	void print() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				printf("%d ", arr[i][j]);
			printf("\n");
		}
	}
};

matrix operator * (matrix a, matrix b) {
	matrix c(a.n, b.m);
	for (int i = 0; i < b.m; i++) {
		for (int j = 0; j < a.m; j++) {
			c.arr[0][i] += (long long)a.arr[0][j] * (long long)b.arr[i][j] % MOD;
			c.arr[0][i] %= MOD;
		}
	}
	for (int i = 1; i < a.n; i++) {
		for (int j = 0; j < b.m; j++) {
			c.arr[i][j] = c.arr[0][(j - i + a.n) % a.n] % MOD;
		}
	}
	return c;
}

matrix pow(matrix a, int b) {
	matrix ans(a.n, a.n);
	for (int i = 0; i < a.n; i++)
		ans.arr[i][i] = 1;
	while (b) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

int n, d, k;

int main() {
	freopen("3150.in", "r", stdin);
	scanf("%d %d %d %d", &n, &MOD, &d, &k);
	matrix origin(1, n);
	for (int i = 0; i < n; i++)
		scanf("%d", &origin.arr[0][i]);
	matrix base(n, n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (abs(i - j) <= d || n - abs(i - j) <= d)
				base.arr[i][j] = 1;
	base = pow(base, k);
	matrix ans(1, n);
	for (int j = 0; j < n; j++) {
		for (int k = 0; k < n; k++) {
			ans.arr[0][j] += (long long)origin.arr[0][k] * (long long)base.arr[k][j] % MOD;
			ans.arr[0][j] %= MOD;
		}
	}
	ans.print();

	return 0;
}
