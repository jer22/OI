#include <bits/stdc++.h>

using namespace std;

int n, m, k;
int hei[105], cost[105], val[105];
int dp[105][2058];

bool check(int x) {
	memset(dp, 0x3f, sizeof(dp));
	if (hei[1] >= x) dp[1][0] = 0;
	dp[1][1] = cost[1];
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < 1 << k; j++) {
			if (dp[i][j] > m) continue;
			int tot = hei[i + 1];
			for (int p = 0; p < k - 1; p++) {
				if ((1 << p) & j) tot += val[i - p];
			}
			if (tot >= x) dp[i + 1][(j << 1) % (1 << k)] = min(dp[i + 1][(j << 1) % (1 << k)], dp[i][j]);
			if (tot + val[i + 1] >= x) dp[i + 1][(j << 1) % (1 << k) + 1] = min(dp[i + 1][(j << 1) % (1 << k) + 1], dp[i][j] + cost[i + 1]);

		}
	}
	for (int i = 0; i < 1 << k; i++)
		if (dp[n][i] <= m) return true;
	return false;
}

int main() {
	freopen("cover9.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	int l = 0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &hei[i], &val[i], &cost[i]);
		l = min(l, hei[i]);
	}
	int r = hei[1] + val[1];

	while (l < r) {
		int mid = (l + r >> 1) + 1;
		if (check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l;

	return 0;
}
