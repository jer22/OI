#include <bits/stdc++.h>

using namespace std;

int n, m;
map<string, bool> exist;
string str[300005];
int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> m;
	string s, ss;
	for (int i = 0; i < n; i++) {
		cin >> str[i];
		
	}
	for (int i = 0; i < m; i++) {
		cin >> s;
		exist[s] = 1;
	}
	for (int i = 0; i < n; i++) {
		ss = str[i];
		int len = ss.size();
		for (int i = 0; i < len; i++) {
			for (int j = 0; j < 3; j++) {
				if ('a' + j == s[i]) continue;
				ss[i] = 'a' + j;
				if (!exist[ss]) continue;
				exist[ss] = 1;
			}
			ss[i] = s[i];
		}
	}

	return 0;
}
