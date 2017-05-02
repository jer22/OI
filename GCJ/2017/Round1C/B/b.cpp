#include <bits/stdc++.h>

using namespace std;

struct Node{
	int a, b, c;
};

int T, n, m;
int vis[1445];
int dp[1445][1445][3];
int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		memset(vis, 0, sizeof(vis));
		for (int i = 1, a, b; i <= n; i++) {
			scanf("%d %d", &a, &b);
			for (int i = a; i < b; i++)
				vis[i] = 1;
		}
		for (int i = 1, a, b; i <= m; i++) {
			scanf("%d %d", &a, &b);
			for (int i = a; i < b; i++)
				vis[i] = 2;
		}
		int INF = 0x3f3f3f3f;
		memset(dp, 0x3f, sizeof(dp));
		if (vis[0] != 1) {
			dp[0][1][1] = 0;
		}
		if (vis[0] != 2) {
			dp[0][0][2] = 0;
		}

		for (int i = 0; i < 1440 - 1; i++) {
			for (int j = 0; j <= min(i + 1, 720); j++) {
				if (dp[i][j][1] != INF) {
					if (vis[i + 1] != 1) {
						if (dp[i][j][1] < dp[i + 1][j + 1][1]) {
							dp[i + 1][j + 1][1] = dp[i][j][1];
						}
					}
					if (vis[i + 1] != 2) {
						dp[i + 1][j][2] = min(dp[i + 1][j][2], dp[i][j][1] + 1);
					}
				}
				if (dp[i][j][2] != INF) {
					if (vis[i + 1] != 1)
						dp[i + 1][j + 1][1] = min(dp[i + 1][j + 1][1], dp[i][j][2] + 1);
					if (vis[i + 1] != 2)
						dp[i + 1][j][2] = min(dp[i + 1][j][2], dp[i][j][2]);
				}
			}
		}
		int ans = 0x3f3f3f3f;
		if (dp[1439][720][1] & 1) ans = min(ans, dp[1439][720][1] + 1);
		else ans = min(ans, dp[1439][720][1]);
		if (dp[1439][720][2] & 1) ans = min(ans, dp[1439][720][2] + 1);
		else ans = min(ans, dp[1439][720][2]);
		printf("Case #%d: ", cas);
		cout << ans << endl;
	}

	return 0;
}
