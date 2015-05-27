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
	freopen("a.in", "w", stdout);
	cout << 1000000 << endl;

	cout << 1 << ' ' << 10 << endl;
	cout << 2 << ' ' << 3 << endl;
	cout << 2 << ' ' << 22 << endl;
	cout << 4 << ' ' << 2 << endl;

	return 0;
}
