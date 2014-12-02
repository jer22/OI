#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int dist[15][15];
int dp[2050][15];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("3311.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (!n) break;
		memset(dist, -1, sizeof(dist));
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				scanf("%d", &dist[i][j]);
			}
		}
		for (int k = 0; k <= n; k++) {
			for (int i = 0; i <= n; i++) {
				for (int j = 0; j <= n; j++) {
					if (i != k && k != j && i != j) {
						dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
					}
				}
			}
		}

		memset(dp, -1, sizeof(dp));
		for (int i = 0; i <= n; i++) {
			dp[1 << i][i] = dist[0][i];
		}
		int ans = 0x3f3f3f3f;
		for (int i = 0; i < 1 << (n + 1); i++) {
			for (int j = 0; j <= n; j++) {
				if (dp[i][j] != -1) {
					for (int k = 0; k <= n; k++) {
						if (!(i & (1 << k))) {
							dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + dist[j][k]);
							if ((i | 1 << k) == (1 << n + 1) - 1) ans = min(ans, dp[i | (1 << k)][k] + dist[k][0]);
						}
					}
				}
			}
		}
		printf("%d\n", ans);
	}
	
	


	return 0;
}
