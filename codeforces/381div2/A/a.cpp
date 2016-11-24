#include <bits/stdc++.h>

using namespace std;

long long n, a, b, c;
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n >> a >> b >> c;
	int t = (4 - (n % 4)) % 4;
	if (!t) cout << 0 << endl;
	else if (t == 1) cout << min(b + c, min(a, c * 3)) << endl;
	else if (t == 2) cout << min(min(a + b + c, c * 2), min(a * 2, b)) << endl;
	else {
		long long ans = min(a * 3, min(c, a + b));
		ans = min(ans, c * 2 + a);
		ans = min(ans, b * 3 + a);
		ans = min(ans, c * 5);
		ans = min(ans, c + b * 2);
		ans = min(ans, c + b + a * 2);
		cout << ans << endl;
	}

	return 0;
}
