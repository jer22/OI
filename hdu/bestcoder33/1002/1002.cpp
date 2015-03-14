#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

long long n, p;

long long hehe(long long a, long long b) {
	long long ans = 0;
	while (b) {
		if (b & 1) ans = (ans + a) % p;
		a = (a + a) % p;
		b >>= 1;
	}
	return ans;
}

long long getans() {
	long long ans = 1;
	long long base = 2;
	while (n) {
		if (n & 1) {
			ans = hehe(ans, base);
			ans %= p;
		}
		base = hehe(base, base);
		base %= p;
		n >>= 1;
	}
	return ans;
}

int main() {
	freopen("1002.in", "r", stdin);
	while (~scanf("%lld %lld", &n, &p)) {
		if (n == 1) {
			if (p == 1) cout << 0 << endl;
			else cout << 1 << endl;
			continue;
		}
		long long ans = getans();
		ans -= 2;
		ans += p;
		ans %= p;
		cout << ans << endl;
	}
	return 0;
}
