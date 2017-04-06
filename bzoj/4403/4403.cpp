#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const unsigned long long MOD = 1000003;

unsigned long long fac[MOD + 2], inv[MOD + 2];
void init() {
	fac[0] = 1;
	for (unsigned int i = 1; i < MOD; i++)
		fac[i] = fac[i - 1] * i % MOD;
	inv[1] = 1;
	for (unsigned int i = 2; i < MOD; i++)
		inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
	inv[0] = 1;
	for (unsigned int i = 1; i < MOD; i++)
		(inv[i] *= inv[i - 1]) %= MOD;
}

unsigned long long C(unsigned int n, unsigned int m) {
	if (n < m) return 0;
	if (n < MOD && m < MOD)
		return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	return C(n / MOD, m / MOD) * C(n % MOD, m % MOD) % MOD;
}

int main() {
	freopen("4403.in", "r", stdin);
	int T;
	init();
	unsigned long long n, l, r;
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld", &n, &l, &r);
		unsigned long long m = r - l + 1;
		printf("%lld\n", (C(n + m, m) + MOD - 1) % MOD);
	}
	return 0;
}
