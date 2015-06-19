#include <bits/stdc++.h>

using namespace std;

int n;
int main() {
	int a, b, c, d;
	cin >> n;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c >> d;
		ans += abs(c - a + 1) * abs(d - b + 1);
	}
	cout << ans << endl;
	return 0;
}
