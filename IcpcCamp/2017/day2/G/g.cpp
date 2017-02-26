#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>

using namespace std;

const int MAXN = 1000006;
const long long INF = LONG_LONG_MAX;

int n;
long long a[MAXN << 1];
long long dp[MAXN << 1][2];
int main() {
	freopen("g.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i * 2 + 1]);
		for (int i = 0; i < n; i++)
			scanf("%lld", &a[i * 2]);
		int m = n << 1;
		long long ans = INF;
		for (int i = 0; i < m; i++)
			dp[i][0] = dp[i][1] = INF;
		dp[1][1] = a[1];
		// dp[1][0] = 0;
		for (int i = 2; i < m; i++) {
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
			dp[i][0] = dp[i - 1][1];
		}
		dp[0][1] = min(dp[m - 1][0], dp[m - 1][1]) + a[0];
		dp[0][0] = dp[m - 1][1];
		ans = min(dp[0][0], dp[0][1]);

		for (int i = 0; i < m; i++)
			dp[i][0] = dp[i][1] = INF;
		// dp[1][1] = a[1];
		dp[1][0] = 0;
		for (int i = 2; i < m; i++) {
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + a[i];
			dp[i][0] = dp[i - 1][1];
		}
		dp[0][1] = min(dp[m - 1][0], dp[m - 1][1]) + a[0];
		dp[0][0] = dp[m - 1][1] + a[1];
		ans = min(ans, min(dp[0][0], dp[0][1]));
		cout << ans << endl;
	}


	return 0;
}
