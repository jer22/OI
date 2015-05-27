#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

const int MOD = 1000000007;

int n, m;
string a, b;
set<string> suba, subb;
set<string> hha, hhb;

int solve(set<string> a, set<string> b) {
	for (set<string>::iterator it = b.begin(); it != b.end(); it++) {
		string s = *it;
		// cout << s << endl;
	}
	int ans = 0;
	for (set<string>::iterator it = a.begin(); it != a.end(); it++) {
		string s = *it;
		if (b.find(s) == b.end()) {
			ans++;
			// cout << s << endl;
		}
	}
	return ans;
}

int main() {
	freopen("b.in", "r", stdin);
	cin >> a >> b;
	n = a.size();
	m = b.size();
	for (int i = 0; i < n; i++) {
		string s = "";
		for (int j = i; j < n; j++) {
			s += a[j];
			suba.insert(s);
		}
	}
	for (int i = 0; i < m; i++) {
		string s = "";
		for (int j = i; j < m; j++) {
			s += b[j];
			subb.insert(s);
		}
	}
	reverse(a.begin(), a.end());
	for (int i = 1; i < 1 << n; i++) {
		string s = "";
		for (int j = 0; 1 << j <= i; j++) {
			if (i & (1 << j)) s += a[j];
		}
		reverse(s.begin(), s.end());
		hha.insert(s);
	}
	for (int i = 1; i < 1 << m; i++) {
		string s = "";
		for (int j = 0; 1 << j <= i; j++) {
			if (i & (1 << j)) s += b[j];
		}
		cout << s << endl;
		hhb.insert(s);
	}
	printf("%d\n%d\n%d\n%d\n", solve(suba, subb), solve(suba, hhb), solve(hha, subb), solve(hha, hhb));

	return 0;
}
