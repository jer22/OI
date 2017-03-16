#include <bits/stdc++.h>

using namespace std;

char s[20];
long long num[20], p[20];

long long mul(long long x, long long y, long long P) {
	return (x * y - (long long)(x / (long double)P * y + 1e-3) * P + P) % P;
}

struct Matrix{
	long long a, b, c, d;
	Matrix(long long _a = 0, long long _b = 0, long long _c = 0, long long _d = 0)
		: a(_a), b(_b), c(_c), d(_d) {}
	friend Matrix multi(Matrix a, Matrix b, long long P) {
		return Matrix(
			(mul(a.a, b.a, P) + mul(a.b, b.c, P)) % P,
			(mul(a.a, b.b, P) + mul(a.b, b.d, P)) % P,
			(mul(a.c, b.a, P) + mul(a.d, b.c, P)) % P,
			(mul(a.c, b.b, P) + mul(a.d, b.d, P)) % P
		);
	}
	friend Matrix power(Matrix a, long long b, long long P) {
		Matrix res = Matrix(1, 0, 0, 1);
		for (; b; b >>= 1ll, a = multi(a, a, P))
			if (b & 1) res = multi(res, a, P);
		return res;
	}
};

long long fib(long long n, long long P) {
	if (!n) return 0;
	return power(Matrix(1, 1, 1, 0), n - 1, P).a;
}

long long solve(long long now, int n, long long P) {
	if (fib(now, p[n]) != num[n]) return -1;
	if (n == 1) return now + 6000000000000000000ll;
	for (long long t, i = 0; i < 10; i++) {
		if (~(t = solve((now + i * P) % (P * 10), n - 1, P * 10))) return t;
	}
	return -1;
}

int main() {
	freopen("4294.in", "r", stdin);
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	p[n + 1] = 1;
	for (int i = n; i >= 1; i--)
		p[i] = p[i + 1] * 10;
	for (int i = 18; i >= 1; i--)
		num[i] = num[i + 1] + ((s[i] - '0') * p[i + 1]);
	long long ans = -1;
	for (long long i = 0; i < 60; i++)
		if (~(ans = solve(i, n, 60))) break;
	if (~ans) printf("%lld\n", ans);
	else printf("NIE\n");

	return 0;
}
