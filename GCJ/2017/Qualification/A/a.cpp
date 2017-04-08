#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char rev[266];
int main() {
	freopen("a.in", "r", stdin);
	freopen("out", "w", stdout);
	int T;
	scanf("%d", &T);
	string s;
	int k;
	rev['+'] = '-';
	rev['-'] = '+';
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> s >> k;
		int len = s.size();
		int num = 0;
		for (int i = len - 1; i - k + 1 >= 0; i--) {
			if (s[i] == '+') continue;
			num++;
			for (int j = i - k + 1; j <= i; j++)
				s[j] = rev[s[j]];
		}
		bool f = 1;
		for (int i = 0; i < k - 1; i++) {
			if (s[i] == '-') {
				f = 0;
				break;
			}
		}
		if (f) cout << num << endl;
		else cout << "IMPOSSIBLE" << endl;
	}


	return 0;
}
