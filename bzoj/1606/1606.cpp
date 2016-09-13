#include <bits/stdc++.h>

using namespace std;

int n, m;
int val[5005];
int dp[2][50005];

int main() {
	freopen("1606.in", "r", stdin);
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);
	dp[1][val[1]] = dp[1][0] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			dp[i & 1][j] = 0;
			if (dp[(i + 1) & 1][j] || (j >= val[i] && dp[(i + 1) & 1][j - val[i]]))
				dp[i & 1][j] = 1;
		}
	}
	int ans = 0;
	for (int i = m; i >= 0; i--) {
		if (dp[n & 1][i]) {
			ans = i;
			break;
		}
	}
	cout << ans << endl;

	return 0;
}
