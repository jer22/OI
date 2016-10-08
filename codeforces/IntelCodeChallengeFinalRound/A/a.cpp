#include <bits/stdc++.h>

using namespace std;

string a, b;
map<string, int> hh;
int main() {
	freopen("a.in", "r", stdin);
	cin >> a >> b;
	int x, y;
	hh["monday"] = 0;
	hh["tuesday"] = 1;
	hh["wednesday"] = 2;
	hh["thursday"] = 3;
	hh["friday"] = 4;
	hh["saturday"] = 5;
	hh["sunday"] = 6;

	x = hh[a], y = hh[b];

	int c = (y + 7 - x) % 7;

	if (c == 3 || c == 0 || c == 2) cout << "YES" << endl;
	else cout << "NO" << endl;


	return 0;
}
