#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const long long p = 10007;

long long n, m;
long long fact[10010];
void init() {
	fact[0] = 1;
	for (int i = 1; i <= p; i++)
		fact[i] = fact[i - 1] * i % p;
}

long long power(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

long long lucas(long long a, long long k) {
	long long re = 1;
	while (a && k) {
		long long aa = a % p;
		long long bb = k % p;
		if (aa < bb) return 0;
		re = re * fact[aa] * power(fact[bb] * fact[aa - bb] % p, p - 2) % p;
		a /= p;
		k /= p;
	}
	return re;
}

int main() {
	freopen("j.in", "r", stdin);
	init();
	while (~scanf("%lld %lld", &m, &n)) {
		printf("%lld\n", lucas(n, m));
	}

	return 0;
}
