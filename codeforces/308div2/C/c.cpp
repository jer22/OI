#include <bits/stdc++.h>

using namespace std;

int n, m;
int main() {
	cin >> n >> m;
	if (n == 3) {
		cout << "YES" << endl;
		return 0;
	}
	while (m) {
		int z = m % n;
		if (z <= 1) {
			m /= n;
		} else if (z == n - 1) {
			m = m / n + 1;
		} else {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;

	return 0;
}
