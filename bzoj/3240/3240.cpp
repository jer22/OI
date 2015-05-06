#include <bits/stdc++.h>

const long long MOD = 1e9 + 7;

using namespace std;

struct matrix{
	long long a[3][3];
	matrix() { memset(a, 0, sizeof(a)); }
	matrix(long long b, long long c, long long d, long long e) {
		memset(a, 0, sizeof(a));
		a[0][0] = b;
		a[0][1] = c;
		a[1][0] = d;
		a[1][1] = e;
	}
	matrix operator * (matrix n) {
		matrix ans;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				for (int k = 0; k < 2; k++)
					ans.a[i][j] = (ans.a[i][j] + a[i][k] * n.a[k][j]) % MOD;
		return ans;
	}
}I;

string s1, s2;
long long a, b, c, d, phi;
long long n, m;

long long get(string s) {
	long long x = 0;
	for (int i = 0; i < s.size(); i++) {
		char c = s[i];
		x = (x * 10 + c - 48) % phi;
	}
	return (x - 1 + phi) % phi;
}

matrix power(matrix a, long long b) {
	matrix ans = I;
	while (b) {
		if (b & 1) ans = ans * a;
		a = a * a;
		b >>= 1;
	}
	return ans;
}

int main() {
	freopen("3240.in", "r", stdin);
	cin >> s1 >> s2;
	scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
	if (a == 1) phi = MOD;
	else phi = MOD - 1;
	n = get(s1);
	if (c == 1) phi = MOD;
	else phi = MOD - 1;
	m = get(s2);
	matrix A = matrix(a, b, 0, 1), B = matrix(c, d, 0, 1);
	I = matrix(1, 0, 0, 1);
	matrix C = power(A, m), D = B * C;
	D = power(D, n);
	D = C * D;
	printf("%lld\n", (D.a[0][1] + D.a[0][0]) % MOD);
	return 0;
}
