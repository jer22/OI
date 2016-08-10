#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
long long n;

long long power(int a, long long b) {
	long long ans = 1;
	long long base = a;
	while (b) {
		if (b & 1) ans = ans * base % 10007;
		b >>= 1;
		base = base * base % 10007;
	}
	return ans;
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%lld", &n);
		long long ans = (power(4, n - 1) + power(2, n - 1)) % 10007;
		printf("%lld\n", ans);
	}


	return 0;
}
