#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n;
bool is_palin(char *s) {
	int len = strlen(s);
	for (int i = 0; i <= len >> 1; i++)
		if (s[i] != s[len - i - 1]) return false;
	return true;
}

int main() {
	freopen("5202.in", "r", stdin);
	while (cin >> n) {
		char s[1005];
		scanf("%s", s);
		char ans[1005];
		for (int i = 0; i < n; i++)
			if (s[i] == '?') ans[i] = 'a';
			else ans[i] = s[i];
		ans[n] = '\0';
		if (!is_palin(ans)) {
			cout << ans << endl;
			continue;
		}
		bool flag = false;
		for (int i = n - 1; i >= 0; i--) {
			if (n % 2 && i == n / 2) continue;
			if (s[i] == '?') {
				ans[i] = 'b';
				cout << ans << endl;
				flag = true;
				break;
			}
			if (flag) break;
		}
		if (!flag) cout << "QwQ" << endl;
	}


	return 0;
}
