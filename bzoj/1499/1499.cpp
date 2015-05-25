#include <bits/stdc++.h>

using namespace std;

int n, m, k, sx, sy;
char arr[205][205];
int s[205], t[205], d[205];
int dp[205][205][205];

int main() {
	freopen("1499.in", "r", stdin);
	scanf("%d %d %d %d %d", &n, &m, &sx, &sy, &k);
	for (int i = 1; i <= n; i++)
		scanf("%s", arr[i] + 1);
	for (int i = 1; i <= k; i++)
		scanf("%d %d %d", &s[i], &t[i], &d[i]);
	memset(dp, -1, sizeof(dp));
	dp[0][sx][sy] = 0;
	for (int now = 1; now <= k; now++) {
		if (d[now] == 1) {
			for (int j = 1; j <= m; j++) {
				for (int i = n; i >= 1; i--) {
					if (arr[i][j] == 'x') continue;
					for (int x = 0; x <= t[now] - s[now] + 1; x++) {
						if (i + x > n) break;
						if (arr[i + x][j] == 'x') break;
						if (dp[now - 1][i + x][j] == -1) continue;
						dp[now][i][j] = max(dp[now][i][j], dp[now - 1][i + x][j] + x);
					}
				}
			}
		}

		if (d[now] == 2) {
			for (int j = 1; j <= m; j++) {
				for (int i = 1; i <= n; i++) {
					if (arr[i][j] == 'x') continue;
					for (int x = 0; x <= t[now] - s[now] + 1; x++) {
						if (i - x < 1) break;
						if (arr[i - x][j] == 'x') break;
						if (dp[now - 1][i - x][j] == -1) continue;
						dp[now][i][j] = max(dp[now][i][j], dp[now - 1][i - x][j] + x);
					}
				}
			}
		}

		if (d[now] == 3) {
			for (int i = 1; i <= n; i++) {
				for (int j = m; j >= 1; j--) {
					if (arr[i][j] == 'x') continue;
					for (int x = 0; x <= t[now] - s[now] + 1; x++) {
						if (j + x > m) break;
						if (arr[i][j + x] == 'x') break;
						if (dp[now - 1][i][j + x] == -1) continue;
						dp[now][i][j] = max(dp[now][i][j], dp[now - 1][i][j + x] + x);
					}
				}
			}
		}

		if (d[now] == 4) {
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					if (arr[i][j] == 'x') continue;
					for (int x = 0; x <= t[now] - s[now] + 1; x++) {
						if (j - x < 1) break;
						if (arr[i][j - x] == 'x') break;
						if (dp[now - 1][i][j - x] == -1) continue;
						dp[now][i][j] = max(dp[now][i][j], dp[now - 1][i][j - x] + x);
					}
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			ans = max(ans, dp[k][i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
