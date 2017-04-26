#include <bits/stdc++.h>

using namespace std;

const int MAXN = 30005;

// class Solution {
// public:
	string s;
	int cnt, last;
	int tr[300005][27], fa[300005], len[300005], siz[300005];
	int pos[300005];
	int dp[300005], mi[300005];
	void extend(int c, int n) {
		int p = last;
		while (s[n - len[p] - 1] != s[n]) p = fa[p];
		if (!tr[p][c]) {
			int now = ++cnt, k = fa[p];
			len[now] = len[p] + 2;
			while (s[n - len[k] - 1] != s[n]) k = fa[k];
			fa[now] = tr[k][c];
			tr[p][c] = now;
		}
		last = tr[p][c];
		siz[last]++;
		pos[n] = last;

		// mi[last] = min(mi[fa[last]], dp[n - len[last] + 1]);
		// dp[n + 1] = mi[last] + 1;
		// cout << dp[n + 1] << endl;
		// if (n == 5) cout << len[fa[last]] << endl; 
	}
	int minCut(string str) {
		int n = str.size();
		s = str;
		fa[0] = fa[1] = 1;
		cnt = 1;
		last = 0;
		len[1] = -1;

		memset(dp, 0x3f, sizeof(dp));
		memset(mi, 0x3f, sizeof(mi));
		dp[0] = 0;
		for (int i = 0; i < n; i++)
			extend(s[i] - 'a', i);

		for (int i = 0; i < n; i++) {
			int p = pos[i];
			// cout << p << ' ' << len[p] << ' ' << i - len[p] + 1 << endl;
			while (p != 1) {
				dp[i + 1] = min(dp[i + 1], dp[i - len[p] + 1] + 1);
				p = fa[p];
			}
		}
		return dp[n] - 1;
	}
// };


string str;
int main() {
	freopen("132.in", "r", stdin);
	cin >> str;
	int ans = minCut(str);
	// int ans = Solution().minCut(s);
	cout << ans << endl;
	return 0;
}
