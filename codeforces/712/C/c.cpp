#include <bits/stdc++.h>

using namespace std;

int x[3], y;
int main() {
	freopen("c.in", "r", stdin);
	cin >> y >> x[0];
	x[1] = x[2] = x[0];
	int idx = 0;
	int ans = 0;
	while (x[idx] != y) {
		int t = x[(idx + 1) % 3] + x[(idx + 2) % 3] - 1;
		x[idx] = min(t, y);
		idx = (idx + 1) % 3;
		ans++;
	}
	cout << ans << endl;

	return 0;
}
