#include <bits/stdc++.h>

using namespace std;

int n, k;
char s[1000005];
int next[1000005];

void getNext() {
	int i = 0, j = -1;
	next[0] = -1;
	while (i < n) {
		if (j == -1 || s[i] == s[j])
			next[++i] = ++j;
		else j = next[j];
	}
}

int main() {
	// freopen("d.in", "r", stdin);
	cin >> n >> k;
	cin >> s;
	getNext();
	for (int i = 1; i <= n; i++) {
		int len = i - next[i];
		int tim = i / len;
		if (!(i % len)) {
			if (tim % k <= tim / k) cout << 1;
			else cout << 0;
		} else {
			if (tim % k < tim / k) cout << 1;
			else cout << 0;
		}
	}
	cout << endl;
	return 0;
}
