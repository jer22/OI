#include <bits/stdc++.h>

using namespace std;

int T;
long long n;
int tot;
long long sum(long long x) {
	long long y = x + 1ll;
	if (x & 1) y >>= 1ll;
	else x >>= 1ll;
	return x * y;
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	int cas = 0;
	while (T--) {
		scanf("%lld", &n);
		long long l = 1, r = 2000000000ll;
		// int cnt = 0;
		while (l < r) {
			// cnt++;
			// if (cnt > 5) break;
			long long m = (l + r >> 1) + 1;
			// cout << sum(m) << endl;
			if (sum(m) <= n) l = m;
			else r = m - 1;
		}
		printf("Case #%d: %lld\n", ++cas, sum(l));
	}

	return 0;
}
