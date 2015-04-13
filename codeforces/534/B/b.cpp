#include <bits/stdc++.h>

using namespace std;

int v0, v1;
int n, d;
int main() {
	// freopen("b.in", "r", stdin);
	cin >> v0 >> v1 >> n >> d;
	int ans = v0;
	for (int i = 1; i < n; i++) {
		int top = v1 + d * (n - 1 - i);
		v0 = min(v0 + d, top);
		ans += v0;
	}
	cout << ans << endl;
	return 0;
}
