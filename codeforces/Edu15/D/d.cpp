#include <bits/stdc++.h>

using namespace std;

long long d, k, a, b, t;
int main() {
	freopen("d.in", "r", stdin);
	cin >> d >> k >> a >> b >> t;
	long long x = d / k;
	long long y = d % k;
	long long ans = 0;
	if (!x) {
		ans = d * a;
	} else {
		ans += k * a;
		ans += min(t + y * a, y * b);
		ans += min(a * k + t, b * k) * (x - 1);
	}
	cout << ans << endl;

	return 0;
}
