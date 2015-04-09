#include <bits/stdc++.h>

using namespace std;

int n, m;
string name[17];
map<string, int> hash;
int vis[255];
string ans[17];
int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> name[i];
		hash[name[i]] = i;
	}
	string a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		int x = hash[a], y = hash[b];
		vis[i] = (1 << x) | (1 << y);
	}
	int k;
	int ansk, tot = 0;
	for (k = (1 << n) - 1; k >= 0; k--) {
		bool flag = false;
		for (int i = 0; i < m; i++) {
			if ((k & vis[i]) == vis[i]) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			int cnt = 0;
			for (int i = 0; i < n; i++)
				if (k & (1 << i))
					cnt++;
			if (cnt > tot) {
				tot = cnt;
				ansk = k;
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (ansk & (1 << i)) {
			ans[cnt++] = name[i];
		}
	}
	sort(ans, ans + tot);
	cout << tot << endl;
	for (int i = 0; i < cnt; i++)
		cout << ans[i] << endl;

	return 0;
}
