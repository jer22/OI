#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
char s[100005];
int cnt[255];
int vis[255];
int main() {
	freopen("c.in", "r", stdin);
	cin >> n;
	cin >> s;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (!cnt[s[i]]) sum++;
		cnt[s[i]]++;
	}
	int l = 0, r;
	int now = 0;
	int ans = 1000000000;
	for (r = 0; r < n; r++) {
		if (!vis[s[r]]) now++;
		vis[s[r]]++;
		while (l < r) {
			if (vis[s[l]] > 1) {
				vis[s[l]]--;
				l++;
			} else break;
		}
		if (now == sum) {
			ans = min(ans, r - l + 1);
		}
	}
	cout << ans << endl;

	return 0;
}
