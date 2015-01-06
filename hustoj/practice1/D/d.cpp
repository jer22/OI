#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
int l[100005];
int r[100005];
long long dp[200005];
int main() {
	freopen("d.in", "r", stdin);
	cin >> n >> k;
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		cin >> l[i] >> r[i];
		tot = max(tot, r[i]);
	}
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 0; i <= tot; i++) {
		dp[i + 1] += dp[i];
		dp[i + 1] %= 1000000007;
		dp[i + k] += dp[i];
		dp[i + k] %= 1000000007;
	}
	for (int i = 1; i <= tot; i++) {
		dp[i] += dp[i - 1];
		dp[i] %= 1000000007;
	}
	for (int i = 1; i <= n; i++) {
		cout << (dp[r[i]] - dp[l[i] - 1] + 1000000007) % 1000000007 << endl;
	}
	return 0;
}
