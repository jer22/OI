#include <bits/stdc++.h>

using namespace std;


int solve(long long l, long long r, long long p, long long k) {
	long long mid = l + r >> 1;
	if (p == mid) return k & 1;
	if (p < mid) return solve(l, mid - 1, p, k / 2);
	return solve(mid + 1, r, p, k / 2);
}

long long n, l, r;
int main() {
	freopen("b.in", "r", stdin);
	cin >> n >> l >> r;
	if (!n) {
		cout << 0 << endl;
		return 0;
	}
	int ans = 0;
	long long t = n;
	long long f = 1;
	while (t) {
		f++;
		t >>= 1;
	}
	f = (1ll << f - 1) - 1;
	for (long long i = l; i <= r; i++)
		if (solve(1, f, i, n)) ans++;
	cout << ans << endl;

	return 0;
}
