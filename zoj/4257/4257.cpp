#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int edges[12][12];
int dp[1050];
int main() {
	freopen("4257.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (!n) break;
		memset(edges, -1, sizeof(-1));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &edges[i][j]);
			}
		}
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < 1 << n; i++) {
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) continue;
				for (int k = 0; k < n; k++) {
					if (j == k || (i & (1 << k))) continue;
					dp[i + (1 << k)] = max(dp[i + (1 << k)], dp[i] + edges[j][k]);
				}
			}
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans = max(ans, dp[(1 << i) ^ ((1 << n) - 1)]);
		}
		printf("%d\n", ans);
	}

	return 0;
}
