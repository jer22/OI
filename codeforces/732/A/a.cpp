#include <bits/stdc++.h>

using namespace std;

int k, r;
int main() {
	freopen("a.in", "r", stdin);
	cin >> k >> r;
	for (int i = 1; i <= 10; i++) {
		int t = k * i % 10;
		if (!t || t == r) {
			cout << i << endl;
			return 0;
		}
	}

	return 0;
}
