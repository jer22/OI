#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

long long n, m;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%lld %lld", &n, &m);
	long long ans = 0;
	while (n != m) {
		if (n > m) swap(n, m);
		long long a = m / n;
		long long b = m % n;
		ans += a;
		m = b;
		if (!m) break;
	}
	printf("%lld\n", ans);

	return 0;
}
