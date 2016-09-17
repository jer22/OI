#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

int T;
long long n;
set<long long> s;
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	s.insert(1);
	long long now = 1;
	for (int i = 0; i < 40; i++) {
		
		s.insert(now);
		long long a = now;
		for (int j = 0; j < 20; j++) {
			s.insert(a);
			long long b = a;
			for (int k = 0; k < 20; k++) {
				s.insert(b);
				long long c = b;
				for (int l = 0; l < 20; l++) {
					s.insert(c);
					c *= 7;
					if (c > 2000000000ll) break;
				}
				b *= 5;
				if (b > 2000000000ll) break;
			}
			a *= 3;
			if (a > 2000000000ll) break;
		}
		now *= 2;
		if (now > 2000000000ll) break;
	}

	while (T--) {
		scanf("%lld", &n);
		set<long long>::iterator it = s.lower_bound(n);
		printf("%lld\n", *it);
	}


	return 0;
}
