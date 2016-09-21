#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300005;

int n, q;
int unread[MAXN];
vector<int> message[MAXN];
int main() {
	freopen("a.in", "r", stdin);
	cin >> n >> q;
	int op, x;
	int ans = 0;
	int idx = 0;
	int tot = 0;
	for (int i = 1; i <= q; i++) {
		cin >> op >> x;
		if (op == 1) {
			ans++;
			message[x].push_back(++tot);
			unread[tot] = 1;
		} else if (op == 2) {
			for (int j = 0; j < message[x].size(); j++) {
				if (unread[message[x][j]]) {
					unread[message[x][j]] = 0;
					ans--;
				}
			}
			message[x].clear();
		} else {
			for (; idx <= x; idx++)
				if (unread[idx]) {
					unread[idx] = 0;
					ans--;
				}
		}
		cout << ans << endl;
	}



	return 0;
}
