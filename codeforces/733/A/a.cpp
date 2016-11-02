#include <bits/stdc++.h>

using namespace std;

char s[105];

bool isc(char c) {
	return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y';
}

int main() {
	// freopen("a.in", "r", stdin);
	cin >> s + 1;
	int pre = 0;
	int ans = 0;
	s[strlen(s + 1) + 1] = 'O';
	for (int i = 1; i <= strlen(s + 1) + 1; i++) {
		if (isc(s[i])) {
			ans = max(ans, i - pre);
			pre = i;
		}
	}
	cout << ans << endl;
	return 0;
}
