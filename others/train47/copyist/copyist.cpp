#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 3;

int k, p, a, b;

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

struct matrix {
	int n, m;
	long long a[MAXN][MAXN];
	matrix(int tn, int tm) {
		n = tn;
		m = tm;
		memset(a, 0, sizeof(a));
	}
};

inline matrix operator * (matrix a, matrix b) {
	if (a.m != b.n) printf("error");
	matrix c(a.n, b.m);
	for (int i = 0; i < a.n; i++) {
		for (int j = 0; j < b.m; j++) {
			for (int k = 0; k < a.m; k++) {
				long long t = a.a[i][k] * b.a[k][j] % p;
				c.a[i][j] = (c.a[i][j] + t) % p;
			}
		}
	}
	return c;
}

inline matrix pow(matrix a, int x) {
	matrix res(a.n, a.m);
	for (int i = 0; i < a.n; i++)
		res.a[i][i] = 1;
	for (; x > 0; x >>= 1, a = a * a)
		if (x & 1) res = res * a;
	return res;
}

int main() {
	freopen("copyist.in", "r", stdin);
	scanf("%d %d %d %d", &k, &p, &a, &b);
	int t = gcd(a, b);
	matrix origin(1, 2);
	origin.a[0][0] = origin.a[0][1] = 1;
	matrix base(2, 2);
	base.a[0][1] = k;
	base.a[1][0] = base.a[1][1] = 1;
	matrix A = origin * pow(base, t - 2);
	matrix B = origin * pow(base, a - 2);
	matrix C = origin * pow(base, b - 2);
	cout << B.a[0][1] << endl << C.a[0][1] << endl << A.a[0][1] << endl;

	return 0;
}
