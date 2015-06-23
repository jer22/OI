#include <bits/stdc++.h>

using namespace std;

int a, b, c;
int main() {
	freopen("b.in", "r", stdin);
	cin >> a >> b >> c;
	bool flag = false;
	for (int i = 0; i <= a; i++) {
		int j = b - i;
		int k = c - j;

		int l = a - i;
		if (j < 0 || k < 0) continue;
		if (l != k) continue;

		if (i == 0 && j == 0 || i == 0 && k == 0 || j == 0 && k == 0) continue;
		flag = 1;
		cout << i << ' ' << j << ' ' << k << endl;
		break;
	}
	if (!flag) cout << "Impossible" << endl;

	return 0;
}
