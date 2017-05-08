#include <bits/stdc++.h>

using namespace std;

int T;
long long a, b, c, d;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		long long dd = __gcd(c, d);
		c /= dd, d /= dd;
		long long t = b / d;
		long long ans = 0;
		if (c == d && a != b) {
			cout << -1 << endl;
			continue;
		}
		if (a * d == b * c) {
			cout << 0 << endl;
			continue;
		} else if (a * d < b * c) {
			if (d * t != b) {
				ans += d * (t + 1) - b;
			}
			b += ans;
			a += ans;
			if (a * d >= b * c) {
				cout << ans << endl;
				continue;
			} else {
				long long p = (a * d - b * c) / (c - d);
				if ((a * d - b * c) % (c - d)) ++p;
				long long pp = p;
				long long tt = p / d;
				if (d * tt != p) pp += d * (tt + 1) - p;

				ans += pp;
				cout << ans << endl;
				continue;
			}
		} else {
			if (d * t != b) {
				ans += d * (t + 1) - b;
			}
			b += ans;
			if (a * d <= b * c) {
				cout << ans << endl;
				continue;
			} else {
				if (c == 0) {
					cout << -1 << endl;
					continue;
				}
				long long p = (a * d - b * c) / c;
				if ((a * d - b * c) % c) ++p;
				long long pp = p;
				long long tt = p / d;
				if (d * tt != p) pp += d * (tt + 1) - p;

				ans += pp;

				cout << ans << endl;
				continue;
			}
		}
	}


	return 0;
}
