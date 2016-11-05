#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

int T, n;
char c;
vector<int> upper, lower;

int main() {
	// freopen("b.in", "r", stdin);
	cin >> T;
	while (T--) {
		cin >> n;
		if (n == 1) {
			cout << "! 1 1" << endl;
			continue;
		}
		upper.clear();
		lower.clear();
		for (int i = 1; i < n; i += 2) {
			cout << "? " << i << ' ' << i + 1 << endl;
			fflush(stdout);
			cin >> c;
			if (c == '>') {
				upper.push_back(i);
				lower.push_back(i + 1);
			} else {
				upper.push_back(i + 1);
				lower.push_back(i);
			}
		}
		if (n & 1) {
			lower.push_back(n);
			upper.push_back(n);
		}
		int mx = upper[0], mi = lower[0];
		for (int i = 1; i < upper.size(); i++) {
			cout << "? " << mx << ' ' << upper[i] << endl;
			fflush(stdout);
			cin >> c;
			if (c == '<') mx = upper[i];
		}
		for (int i = 1; i < lower.size(); i++) {
			cout << "? " << mi << ' ' << lower[i] << endl;
			fflush(stdout);
			cin >> c;
			if (c == '>') mi = lower[i];
		}
		cout << "! " << mi << ' ' << mx << endl;
	}
	return 0;
}
