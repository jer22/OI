#include <bits/stdc++.h>

using namespace std;

int n;
long long cost[100005];
long long dp[100005][2];
string s[100005], rs[100005];

int main() {
	freopen("c.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> cost[i];
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		rs[i] = s[i];
		reverse(rs[i].begin(), rs[i].end());
	}
	for (int i = 2; i <= n; i++)
		dp[i][0] = dp[i][1] = 1000000000000000000;
	dp[1][1] = cost[1];
	for (int i = 2; i <= n; i++) {
		if (s[i] >= s[i - 1]) dp[i][0] = dp[i - 1][0];
		if (s[i] >= rs[i - 1]) dp[i][0] = min(dp[i][0], dp[i - 1][1]);
		if (rs[i] >= s[i - 1]) dp[i][1] = dp[i - 1][0] + cost[i];
		if (rs[i] >= rs[i - 1]) dp[i][1] = min(dp[i][1], dp[i - 1][1] + cost[i]);
	}
	long long ans = min(dp[n][0], dp[n][1]);
	if (ans == 1000000000000000000) ans = -1;
	cout << ans << endl;

	return 0;
}
