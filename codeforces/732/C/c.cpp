#include <bits/stdc++.h>

using namespace std;

long long a[3];

long long solve() {
	long long t = max(a[0], max(a[1], a[2]));
	long long ans = t * 3 - a[0] - a[1] - a[2];
	if (a[2] < t) {
		ans--;
		if (a[1] < t) ans--;
	}
	return ans;
}

void deal() {
	swap(a[0], a[1]);
	swap(a[1], a[2]);
}

int main() {
	freopen("c.in", "r", stdin);
	cin >> a[0] >> a[1] >> a[2];
	long long ans = solve();
	deal();
	ans = min(ans, solve());
	deal();
	ans = min(ans, solve());
	cout << ans << endl;
	return 0;
}
