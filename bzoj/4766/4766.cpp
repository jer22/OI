#include <bits/stdc++.h>

using namespace std;

long long n, m, p;

long long mul(long long x, long long y) {
	return (x * y - (long long)(x / (long double)p * y + 1e-3) * p + p) % p;
}

long long power(long long a, long long b) {
	long long ans = 1ll, base = a;
	for (; b; b >>= 1ll, base = mul(base, base))
		if (b & 1ll) ans = mul(ans, base);
	return ans;
}

int main() {
	freopen("4766.in", "r", stdin);
	scanf("%lld %lld %lld", &n, &m, &p);
	printf("%lld\n", mul(power(n, m - 1), power(m, n - 1)));

	return 0;
}
