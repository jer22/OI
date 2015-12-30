#include <bits/stdc++.h>

using namespace std;

long long l, r;

int get(long long x) {
	if (!x) return 0;
	if (x == 1) return 0;
	long long m = x;
	int idx = 0;
	bool flag = false;
	int cu = 0;
	int cc = 0;
	while (m) {
		cu++;
		if (!(m & 1)) {
			cc++;
			idx = cu;
		}
		m >>= 1;
	}
	int ans = 0;
	for (int i = cu - 2; i; i--) {
		// cout << i << endl;
		ans += i;
	}
	ans += cu - idx - 1;
	if (cc == 1) ans++;
	return ans;
}

int main() {
	// freopen("b.in", "r", stdin);
	cin >> l >> r;
	int a = get(l - 1);
	int b = get(r);
	cout << b - a << endl;

	return 0;
}
