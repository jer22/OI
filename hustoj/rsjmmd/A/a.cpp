#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
string t;
int main() {
	// freopen("a.in",  "r", stdin);
	cin >> n;
	int ans = 0;
	string tt = "00";
	for (int i = 0; i < n; i++) {
		cin >> t;
		if (t != tt) {
			tt = t;
			ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
