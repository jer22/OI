#include <bits/stdc++.h>

using namespace std;

int x;
string a;
int main() {
	// freopen("a.in", "r", stdin);
	scanf("%d", &x);
	cin >> a;
	cin >> a;
	if (a[0] == 'w') {
		if (x == 5 || x == 6) cout << 53 << endl;
		else cout << 52 << endl;
	} else {
		if (x == 31) cout << 7 << endl;
		else if (x == 30) cout << 11 << endl;
		else cout << 12 << endl;
	}

	return 0;
}
