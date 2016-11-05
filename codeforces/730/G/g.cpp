#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 205;

int n;
int s[MAXN], d[MAXN];

int ok(int idx, int l, int r) {
	for (int i = 1; i < idx; i++) {
		if (l <= s[i] + d[i] - 1 && r >= s[i]) return i;
	}
	return 0;
}

int main() {
	// freopen("g.in", "r", stdin);
	cin >> n;
	d[0] = 1;
	for (int i = 1; i <= n; i++){
		cin >> s[i] >> d[i];
		int idx = ok(i, s[i], s[i] + d[i] - 1);
		if (!idx) continue;
		s[i] = 1;
		idx = ok(i, s[i], s[i] + d[i] - 1);
		while (idx) {
			s[i] = s[idx] + d[idx];
			idx = ok(i, s[i], s[i] + d[i] - 1);
		}
	}
	for (int i = 1; i <= n; i++)
		cout << s[i] << ' ' << s[i] + d[i] - 1 << endl;
	return 0;
}
