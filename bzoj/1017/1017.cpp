#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

int n, m;
int str[55];
int pri[55];
int lim[55];
int num[55];	//i的子树的个数
int son[55][55]; // son[x][i]：物品x的第i个原料
int cnt[55][55]; // cnt[x][i]：物品x的第i个原料所需的数目
int dp[55][2005][105];
int g[55][2005];

void dfs(int x) {
	for (int i = 1; i <= num[x]; i++) {
		dfs(son[x][i]);
		lim[x] = min(lim[x], lim[son[x][i]] / cnt[x][i]);
		pri[x] += cnt[x][i] * pri[son[x][i]];
	}
	lim[x] = min(lim[x], m / pri[x]); // 这句话不能忘，总钱数与单价也限制了数量
}

void DP(int x) {
	if (!num[x]) {
		for (int i = 0; i <= lim[x]; i++) {
			for (int j = 0; j <= i; j++) {
				dp[x][i * pri[x]][j] = str[x] * (i - j);
			}
		}
		return;
	}
	for (int i = 1; i <= num[x]; i++) DP(son[x][i]);
	for (int t = 0; t <= lim[x]; t++) { // 枚举合成t件x
		memset(g, -0x3f3f3f3f, sizeof(g));
		g[0][0] = 0;
		for (int i = 1; i <= num[x]; i++) {
			for (int j = 0; j <= m; j++) {
				for (int k = 0; k <= j; k++) { // 此处枚举第i棵子树的花费k
					g[i][j] = max(g[i][j], g[i - 1][j - k] + dp[son[x][i]][k][t * cnt[x][i]]);
				}
			}
		}
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= t; k++) { // k件用于上层合成
				dp[x][j][k] = max(dp[x][j][k], g[num[x]][j] + str[x] * (t - k));
			}
		}
	}
}

int main() {
	scanf("%d %d", &n, &m);
	char ty[3];
	memset(lim, 0x3f, sizeof(lim));
	int root = 0;
	for (int i = 1; i <= n; i++) {
		root += i;
		scanf("%d", &str[i]);
		scanf("%s", ty);
		if (ty[0] == 'A') {
			scanf("%d", &num[i]);
			for (int j = 1; j <= num[i]; j++) {
				scanf("%d %d", &son[i][j], &cnt[i][j]);
				root -= son[i][j];
			}
		} else scanf("%d %d", &pri[i], &lim[i]);
	}
	dfs(root); // 一遍dfs计算出所有物品的单价和数量上限
	memset(dp, -0x3f3f3f3f, sizeof(dp));
	DP(root);
	int ans = 0;
	for (int i = 0; i <= m; i++)
		ans = max(ans, dp[root][i][0]);
	printf("%d\n", ans);
	return 0;
}
