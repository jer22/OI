#include <bits/stdc++.h>

using namespace std;

int n;
int l[5], r[5];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= 3; i++) {
		cin >> l[i] >> r[i];
	}
	for (int a = r[1]; a >= l[1]; a--) {
		int t = n - a - r[2];
		if (t >= l[3] && t <= r[3]) {
			cout << a << ' ' << r[2] << ' ' << t << endl;
			return 0;
		} else {
			if (t < l[3]) {
				int tt = l[3] - t;
				int b = r[2];
				b -= tt;
				if (b >= l[2]) {
					cout << a << ' ' << b << ' ' << l[3] << endl;
					return 0;
				}
			}
		}
	}
	

	return 0;
}
