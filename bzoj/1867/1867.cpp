#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) {
	if (!b) return a;
	return gcd(b, a % b);
}

struct Num{
	long long up, dn;
	Num() { up = 0, dn = 1; }
	Num(long long a, long long b) : up(a), dn(b) {}
	void fuck() {
		long long t = gcd(up, dn);
		up /= t;
		dn /= t;
	}
	void print() {
		cout << up << '/' << dn;
	}
};

Num operator * (Num a, Num b) {
	Num c = Num(a.up * b.up, a.dn * b.dn);
	c.fuck();
	return c;
}

Num operator + (Num a, Num b) {
	long long t = gcd(a.dn, b.dn);
	Num c = Num(b.dn / t * a.up + a.dn / t * b.up, a.dn / t * b.dn);
	c.fuck();
	return c;
}

int n, m;
char arr[55][55];
Num dp[55][55];
char get() {
	char c = getchar();
	while (c == '\n' || c == ' ' || c == '\r' || c == '\t')
		c = getchar();
	return c;
}

int main() {
	freopen("1867.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			arr[i][j] = get();
	dp[1][1] = Num(1, 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (arr[i][j] == '*') {
				dp[i + 1][j] = dp[i + 1][j] + dp[i][j] * Num(1, 2);
				dp[i + 1][j + 1] = dp[i + 1][j + 1] + dp[i][j] * Num(1, 2);
			} else dp[i + 2][j + 1] = dp[i + 2][j + 1] + dp[i][j];
		}
	}
	dp[n + 1][m + 1].print();
	return 0;
}
