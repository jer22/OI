#include <bits/stdc++.h>

#define pii pair<long long, long long>
#define mp(i, j) make_pair(i, j)

using namespace std;

long long mod;
long long h1, a1, x1, yy1;
long long h2, a2, x2, yy2;
long long t1, t2;

map<pii, bool> vis;

long long gcd(long long a, long long b) {
	if (!b) return a;
	return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
	if (!a) return b;
	if (!b) return a;
	long long t = gcd(a, b);
	return a * b / t;
}

int main() {
	freopen("a.in", "r", stdin);
	cin >> mod;
	cin >> h1 >> a1 >> x1 >> yy1;
	cin >> h2 >> a2 >> x2 >> yy2;
	if (h1 == a1 && h2 == a2) {
		cout << 0 << endl;
		return 0;
	}
	vis[mp(h1, h2)] = 1;
	int t;
	for (t = 1; t <= 5000000; t++) {
		h1 = (h1 * x1 + yy1) % mod;
		h2 = (h2 * x2 + yy2) % mod;
		if (h1 == a1 && h2 == a2) {
			cout << t << endl;
			return 0;
		}
		if (vis[mp(h1, h2)]) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << -1 << endl;
	return 0;
}
