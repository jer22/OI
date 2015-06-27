#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, t, r;
int tim[305];
int vis[305];
int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> t >> r;
	int a;
	for (int i = 1; i <= n; i++)
		cin >> tim[i];
	if (t < r) {
		cout << "-1" << endl;
		return 0;
	}
	int ans = 0;
	for (int i = 1; i <= r; i++, t--) {
		memset(vis, 0, sizeof(vis));
		for (int j = 1; j <= n; j++) {
			if (!vis[j]) {
				for (int k = j; k <= n; k++) {
					if (tim[k] - tim[j] >= t) break;
					vis[k] = 1;
				}
				ans++;
			}
		}

	}
	cout << ans << endl;
	return 0;
}
