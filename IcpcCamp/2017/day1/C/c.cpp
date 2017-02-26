#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int vis[55][55];
int p[15];
int dp[55][1600000];
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0, a, b; i < m; i++) {
		scanf("%d %d", &a, &b);
		vis[a][b] = vis[b][a] = 1;
	}
	memset(dp, 0, sizeof(dp));
	p[0] = 1;
	for (int i = 1; i <= 14; i++)
		p[i] = p[i - 1] * 3;
	dp[1][0] = dp[1][1] = dp[1][2] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < p[13]; j++) {
			if (!dp[i][j]) continue;
			int v[3] = {0};
			for (int k = 0; k < min(13, i); k++) {
				if (vis[i + 1][i - min(13, k)])
					v[(j / p[k]) % 3]++;
			}
			(dp[i + 1][j * 3 % p[13]] += dp[i][j]) &= 3;
			if (!v[1]) {
				(dp[i + 1][j * 3 % p[13] + 2] += dp[i][j]) &= 3;
			}
			if (!v[2]) {
				(dp[i + 1][j * 3 % p[13] + 1] += dp[i][j]) &= 3;
			}
		}
	}
	int ans = 3;
	for (int i = 0; i < p[13]; i++)
		(ans += dp[n][i]) &= 3;
	cout << ans / 2 << endl;

	return 0;
}
