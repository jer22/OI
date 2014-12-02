#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

int n;
string str[55];
string ans[55];

string getAns(int i) {
	bool flag = false;
	string s = str[i];
	for (int len = 1; len <= str[i].size(); len++) {
		flag = false;
		s = str[i].substr(0, len);
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (str[j].find(s) == 0) {
				flag = true;
			}
		}
		if (!flag) break;
	}
	return s;
}

int main() {
	freopen("abbreviate.in", "r", stdin);
	freopen("abbreviate.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		cin >> str[i];
	}
	for (int i = 0; i < n; i++) {
		ans[i] = getAns(i);
		cout << ans[i] << '\n';
	}

	return 0;
}
