#include <bits/stdc++.h>

using namespace std;

string a, b;
int main() {
	freopen("a.in", "r", stdin);
	cin >> a >> b;
	int n;
	cin >> n;
	cout << a << ' ' << b << endl;
	string c, d;
	for (int i = 1; i <= n; i++) {
		cin >> c >> d;
		if (c == a) a = d;
		if (c == b) b = d;
		cout << a << ' ' << b << endl;
	}

	return 0;
}
