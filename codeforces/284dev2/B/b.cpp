#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <map>

using namespace std;

int n, m;
map<string, string> dict;
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	string a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		dict[a] = b;
	}
	for (int i = 0; i < n; i++) {
		if (i) cout << ' ';
		cin >> a;
		b = dict[a];
		int la = a.size();
		int lb = b.size();
		if (la != lb) {
			if (la < lb) {
				cout << a;
			} else {
				cout << b;
			}
		} else {
			cout << a;
		}
	}
	cout << endl;
	return 0;
}
