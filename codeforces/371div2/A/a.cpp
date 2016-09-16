#include <bits/stdc++.h>

using namespace std;

long long l1, r1, l2,  r2, k;
int main() {
	freopen("a.in", "r", stdin);
	cin >> l1 >> r1 >> l2 >> r2 >> k;
	long long l = max(l1, l2);
	long long r = min(r1, r2);
	long long ans = r - l + 1;
	if (l <= k && r >= k) ans--;
	ans = max(ans, 0ll);
	cout << ans << endl;



	return 0;
}
