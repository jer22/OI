#include <bits/stdc++.h>

const int MAXN = 5;

using namespace std;

long long m, a, c, x0, n, g;
struct matrix {
	long long x, y;
	matrix() {}
	matrix(long long a, long long b) : x(a), y(b) {}
}origin;

long long mult(long long a, long long b) {
	long long ans = 0;
	while (b) {
		if (b & 1) ans = (ans + a) % m;
		a = (a + a) % m;
		b >>= 1;
	}
	return ans;
}

inline matrix operator * (matrix a, matrix b) {
	return matrix(mult(a.x, b.x), (mult(a.x, b.y) + a.y) % m);
}

inline matrix pow(matrix a, long long x) {
	matrix res = a;
	x--;
	while (x) {
		if (x & 1) {
			res = res * a;
		}
		x >>= 1;
		a = a * a;
	}
	return res;
}

int main() {
	scanf("%lld %lld %lld %lld %lld %lld", &m, &a, &c, &x0, &n, &g);
	origin = matrix(a, c);
	origin = pow(origin, n);
	printf("%lld\n", (mult(origin.x, x0) + origin.y) % m % g);
	return 0;
}
