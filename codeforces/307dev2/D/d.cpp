#include <bits/stdc++.h>

using namespace std;

long long n, k, l, m;

struct matrix{
	int n, m;
	long long arr[2][2];
	matrix(int a, int b) {
		n = a, m = b;
		memset(arr, 0, sizeof(arr));
	}
};

matrix operator * (matrix a, matrix b) {
	matrix c(a.n, b.m);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < b.m; j++) {
			for (int p = 0; p < a.m; p++) {
				long long t = a.arr[i][p] * b.arr[p][j] % m;
				c.arr[i][j] += t;
				c.arr[i][j] %= m;
			}
		}
	}
	return c;
}

matrix pow(matrix a, long long b) {
	matrix c(2, 2);
	c.arr[0][0] = c.arr[1][1] = 1;
	while (b) {
		if (b & 1) c = c * a;
		a = a * a;
		b >>= 1;
	}
	return c;
}

bool judge() {
	long long t = k;
	for (int i = 0; i < l; i++) t >>= 1;
	return t == 0;
}


long long DP() {
	matrix ans(1, 2);
	ans.arr[0][0] = ans.arr[0][1] = 1;
	matrix base(2, 2);
	base.arr[0][1] = base.arr[1][0] = base.arr[1][1] = 1;
	base = pow(base, n);
	ans = ans * base;
	return ans.arr[0][1];
}

long long power(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1)
			ans = ans * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return ans;
}

int main() {
	cin >> n >> k >> l >> m;
	if (!judge()) {
		cout << 0 << endl;
		return 0;
	}
	long long ans = 1;
	long long a = DP();
	long long b = (power(2ll, n) - a + m) % m;
	for (int i = 0; i < l; i++) {
		if ((k >> i) & 1)
			ans = ans * b % m;
		else ans = ans * a % m;
	}
	cout << ans % m << endl;
	return 0;
}
