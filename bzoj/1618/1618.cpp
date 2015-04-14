#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, h;
int wei[105], cost[105];
int dp[55005];
int main() {
	freopen("1618.in", "r", stdin);
	scanf("%d %d", &n, &h);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &wei[i], &cost[i]);
	memset(dp, 128, sizeof(dp));
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		cost[i] = -cost[i];
		for (int j = wei[i]; j <= h + 5000; j++) {
			dp[j] = max(dp[j], dp[j - wei[i]] + cost[i]);
		}
	}
	int ans = -0x3f3f3f3f;
	for (int i = h; i <= h + 5000; i++)
		ans = max(ans, dp[i]);
	cout << -ans << endl;

	return 0;
}
