#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int l[155], r[155];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	getchar();
	char c;
	memset(l, 0x3f, sizeof(l));
	memset(r, -1, sizeof(r));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			c = getchar();
			if (c == 'W') {
				l[i] = min(l[i], j);
				r[i] = max(r[i], j);
			}
		}
		getchar();
	}
	int pos = 0;
	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (l[i] <= r[i]) {
			cnt = i;
			if (i % 2) {
				ans += abs(pos - r[i]) + r[i] - l[i];
				pos = l[i];
			} else {
				ans += abs(pos - l[i]) + r[i] - l[i];
				pos = r[i];
			}
		}
	}
	cout << ans + cnt << endl;
	return 0;
}
