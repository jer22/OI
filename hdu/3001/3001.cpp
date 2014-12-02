#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int edges[15][15];
int dp[59150][15];
int dig[59150][15];
int tri[12] = {0, 1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049};

void init() {
	for (int i = 0; i < tri[11]; i++) {
		int t = i;
		for (int j = 1; j <= 10; j++) {
			dig[i][j] = t % 3;
			t /= 3;
			if (!t) break;
		}
	}
}

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("3001.in", "r", stdin);
	init();
	while (~scanf("%d %d", &n, &m)) {
		memset(edges, -1, sizeof(edges));
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			if (c < edges[a][b] || edges[a][b] == -1)
				edges[a][b] = edges[b][a] = c;
		}
		memset(dp, -1, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			dp[tri[i]][i] = 0;
		}
		int ans = -1;
		for (int S = 0; S < tri[n + 1]; S++) {
			int complete = 1;
			for (int i = 1; i <= n; i++) {
				if (!dig[S][i]) complete = 0;
				if (dp[S][i] != -1) {
					for (int k = 1; k <= n; k++) {
						if (edges[i][k] == -1 || dig[S][k] > 1) continue;
						dp[S + tri[k]][k] = min(dp[S + tri[k]][k], dp[S][i] + edges[i][k]);
					}
				}
			}
			if (complete) {
				for (int j = 1; j <= n; j++) {
					ans = min(ans, dp[S][j]);
				}
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}
