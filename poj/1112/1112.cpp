#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
bool edges[105][105];
bool vis[105];
int cnt[105][2];
int col[105];
int set[105][2][105];
int dp[105][105];
int pre[105][105];

bool dfs(int i, int tot) {
	vis[i] = 1;
	set[tot][col[i]][++cnt[tot][col[i]]] = i;
	for (int j = 1; j <= n; j++) {
		if (j == i) continue;
		if (!edges[i][j]) continue;
		if (!vis[j]) {
			col[j] = col[i] ^ 1;
			if (!dfs(j, tot))
				return false;
		} else {
			if (col[j] == col[i]) return false;
		}
	}
	return true;
}

int main() {
	freopen("1112.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int t;
		memset(edges, 0, sizeof(edges));
		for (int i = 1; i <= n; i++)
			while (scanf("%d", &t) && t)
				edges[i][t] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i == j) continue;
				edges[i][j] ^= 1;
				if (i > j) {
					edges[i][j] = edges[j][i] = (edges[i][j] | edges[j][i]);
				}
			}
		}
		memset(vis, 0, sizeof(vis));
		memset(cnt, 0, sizeof(cnt));
		memset(col, 0, sizeof(col));
		memset(set, 0, sizeof(set));
		int tot = 0;
		bool done = true;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				if (!dfs(i, ++tot)) {
					printf("No solution");
					done = false;
					break;
				}
			}
		}
		if (!done) continue;
		memset(dp, 0, sizeof(dp));
		memset(pre, -1, sizeof(pre));
		dp[0][0] = 1;
		for (int i = 1; i <= tot; i++) {
			for (int j = 0; j <= n / 2; j++) {
				dp[i][j] = 0;
				if (j - cnt[i][0] >= 0 && dp[i - 1][j - cnt[i][0]]) {
					dp[i][j] = 1;
					pre[i][j] = 0;
				}
				if (j - cnt[i][1] >= 0 && dp[i - 1][j - cnt[i][1]]) {
					dp[i][j] = 1;
					pre[i][j] = 1;
				}
			}
		}

		int k;
		for (k = n / 2; k >= 1; k--)
			if (dp[tot][k]) break;
		if (!k) {
			printf("No solution");
			continue;
		}

		int flag[105];
		memset(flag, 0, sizeof(flag));
		int tmp = k;
		for (int i = tot; i >= 1; i--) {
			int t = pre[i][tmp];
			tmp = tmp - cnt[i][t];
			for (int j = 1; j <= cnt[i][t]; j++) {
				flag[set[i][t][j]] = 1;
			}
		}
		printf("%d", n - k);
		for (int i = 1; i <= n; i++) {
			if (!flag[i]) printf(" %d", i);
		}
		printf("\n");
		printf("%d", k);
		for (int i = 1; i <= n; i++) {
			if (flag[i]) printf(" %d", i);
		}
		printf("\n");
	}


	return 0;
}
