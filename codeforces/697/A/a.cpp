#include <bits/stdc++.h>

using namespace std;

int t, s, x;
int main() {
	freopen("a.in", "r", stdin);
	cin >> t >> s >> x;
	if (x < t) {
		cout << "NO" << endl;
	} else {
		x -= t;
		if (x == 1 && s != 1) cout << "NO" << endl;
		else if (!(x % s) || !((x - 1) % s)) cout << "YES" << endl;
		else cout << "NO" << endl;
	}

	return 0;
}
