#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int T, typ;
long long y, z, p;

long long power(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}

map<long long, int> mp;
long long solve() {
	y %= p;
	if (!y && !z) return 1;
	if (!y) return -1;
	long long m = ceil(sqrt(p));
	mp.clear();
	mp[1] = 0;
	long long t = 1;
	for (long long i = 1; i < m; i++) {
		t = t * y % p;
		if (!mp[t]) mp[t] = i;
	}
	long long c = power(y, p - m - 1);
	long long ine = 1;
	for (long long k = 0; k < m; k++) {
		if (mp[z * ine % p])
			return k * m + mp[z * ine % p];
		ine = ine * c % p;
	}
	return -1;
}

int main() {
	freopen("2242.in", "r", stdin);
	scanf("%d %d", &T, &typ);
	while (T--) {
		scanf("%lld %lld %lld", &y, &z, &p);
		if (typ == 1)
			printf("%lld\n", power(y, z));
		else if (typ == 2) {
			long long c = power(y, p - 2);
			long long ans = z * c % p;
			if (ans * y % p == z % p) printf("%lld\n", ans);
			else printf("Orz, I cannot find x!\n");
		} else {
			long long ans = solve();
			if (ans == -1) printf("Orz, I cannot find x!\n");
			else printf("%lld\n", ans); 
		}
	}


	return 0;
}
