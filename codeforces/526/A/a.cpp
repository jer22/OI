#include <bits/stdc++.h>

using namespace std;

int n;
char str[105];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	cin >> str + 1;
	bool flag = false;
	for (int k = 1; k * 4 + 1 <= n; k++) {
		for (int i = 1; k * 4 + i <= n; i++) {
			if (str[i] == '.') continue;
			int cnt = 0;
			for (int j = i; j <= n; j += k) {
				if (str[j] != '*' || cnt == 5) break;
				cnt++;
			}
			if (cnt == 5) {

				flag = true;
				break;
			}

		}
		if (flag) break;
	}
	if (flag) cout << "yes" << endl;
	else cout << "no" << endl;
	return 0;
}
