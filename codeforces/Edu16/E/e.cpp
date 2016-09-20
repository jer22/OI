#include <bits/stdc++.h>

using namespace std;

int n;
long long x, y;
long long dp[10000002];

int main() {
	freopen("e.in", "r", stdin);
	cin >> n >> x >> y;

	dp[1] = x;
	for (int i = 2; i <= n; i++) {
		dp[i] = dp[i - 1] + x;
		if (!(i & 1)) dp[i] = min(dp[i], dp[i >> 1] + y);
		else dp[i] = min(dp[i], dp[i + 1 >> 1] + x + y);
	}
	cout << dp[n] << endl;

	return 0;
}
