#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <cmath>

using namespace std;

int T, n, m;
long long ip[1005];
long long mask[1005];

int solve(long long k) {
	set<long long> s;
	for (int i = 0; i < n; i++) {
		s.insert(k & ip[i]);
	}
	return int(s.size());
}

int main() {
	freopen("1003.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d %d", &n, &m);
		long long a, b, c, d;
		char t;
		for (int i = 0; i < n; i++) {
			scanf("%lld%c%lld%c%lld%c%lld", &a, &t, &b, &t, &c, &t, &d);
			ip[i] = (a << 24) + (b << 16) + (c << 8) + d;
		}
		for (int i = 0; i < m; i++) {
			scanf("%lld%c%lld%c%lld%c%lld", &a, &t, &b, &t, &c, &t, &d);
			mask[i] = (a << 24) + (b << 16) + (c << 8) + d;
		}
		printf("Case #%d:\n", cas++);
		for (int i = 0; i < m; i++) {
			printf("%d\n", solve(mask[i]));
		}
	}

	cout << cos(30);
	return 0;
}
