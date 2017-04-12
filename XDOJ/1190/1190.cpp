#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define unsigned unsigned long long

using namespace std;

unsigned power(unsigned a, unsigned b, unsigned p) {
	unsigned ans = 1;
	for (; b; (a *= a) %= p, b >>= 1)
		if (b & 1) (ans *= a) %= p;
	return ans;
}

unsigned n, p;
int main() {
	freopen("1190.in", "r", stdin);
	while (~scanf("%lld %lld", &n, &p)) {
		unsigned inv = power(6, p - 2, p);
		unsigned a = n % p;
		unsigned b = (n + 1) % p;
		unsigned c = (n * 2 + 1) % p;
		unsigned d = a * b % p;
		unsigned e = c * inv % p;
		unsigned ans = e * d % p;

		cout << ans << endl;
	}

	return 0;
}
