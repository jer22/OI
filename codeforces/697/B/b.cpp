#include <bits/stdc++.h>

using namespace std;

char ans[205];
int len = 0;
string s;
int main() {
	freopen("b.in", "r", stdin);
	cin >>  s;
	int e = 0;
	bool flag = 0;
	int idx;
	for (int i = 0; i < s.size(); i++) {
		if (!flag) {
			if (s[i] == '.') {
				idx = i;
			} else if (s[i] == 'e') {
				flag = 1;
			} else {
				ans[len++] = s[i];
			}
		} else {
			e = e * 10 + s[i] - '0';
		}
	}
	idx += e;
	if (ans[len - 1] == '0') len--;
	for (int i = 0; i < len; i++) {
		if (i == idx) cout << '.';
		cout << ans[i];
	}
	if (idx > len) for (int i = 0; i < idx - len; i++) cout << '0';
	cout << endl;

	return 0;
}
