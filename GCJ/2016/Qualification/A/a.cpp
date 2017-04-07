#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	unsigned int T, n;
	cin >> T;
	char vis[15];
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d: ", cas);
		cin >> n;
		memset(vis, 0, sizeof(vis));
		int cnt = 0;
		if (n == 0) {
			cout << "INSOMNIA" << endl;
			continue;
		}
		unsigned int t = 0;
		while (cnt < 10) {
			t += n;
			unsigned int tt = t;
			while (tt) {
				if (!vis[tt % 10]) cnt++;
				vis[tt % 10] = 1;
				tt /= 10;
			}
		}
		cout << t << endl;
	}


	return 0;
}
