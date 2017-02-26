#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n;
string str[MAXN];
int len[MAXN];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		cin >> str[i];
		len[i] = str[i].size();
	}
	for (int i = n - 1; i >= 1; i--) {
		if (str[i] > str[i + 1]) {
			int t = 1;
			for (int j = 1; j < min(len[i], len[i + 1]) && str[i][j] <= str[i + 1][j]; j++) {
				t++;
			}
			str[i] = str[i].substr(0, t);
		}
	}
	for (int i = 1; i <= n; i++) {
		// for (int j = 0; j < len[i]; j++)
			// cout << str[i][j];
		cout << str[i] << '\n';
	}

	return 0;
}
