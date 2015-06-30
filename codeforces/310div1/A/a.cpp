#include <bits/stdc++.h>

using namespace std;

int n, m;
int main() {
	// freopen("a.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int k, t, tt;
	int res = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		scanf("%d", &t);
		if (t != 1) res += k + k - 1;
		bool flag = false;
		for (int i = 1; i < k; i++) {
			scanf("%d", &tt);
			if (t == 1) {
				if (tt != t + i) flag = 1;
				if (flag) res += 2;
			}
		}
	}
	// res += n - 1;
	cout << res << endl;

	return 0;
}
