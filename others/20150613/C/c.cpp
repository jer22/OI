#include <bits/stdc++.h>

using namespace std;

int main() {
	// freopen("c.in", "r", stdin);
	int a, b, c;
	cin >> a >> b >> c;
	int ans = max(b - a - 1, c - b - 1);
	cout << ans << endl;

	return 0;
}
