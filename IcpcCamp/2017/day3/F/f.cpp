#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch (x << 1)
#define rch (x << 1 | 1)

using namespace std;

const int MAXN = 200005;

int n;
int val[MAXN], pos[MAXN];
int arr[MAXN], dp[MAXN][2];

void dfs(int x) {
	dp[x][0] = 0;
	dp[x][1] = 1;
	if (lch <= n) {
		dfs(lch);
		dp[x][0] = dp[lch][1];
		dp[x][1] += dp[lch][1];
	}
	if (rch <= n) {
		dfs(rch);
		dp[x][0] = max(dp[x][0], dp[rch][1]);
		dp[x][1] += dp[rch][1];
	}
}

void update(int x) {
	if (!x) return;
	dp[x][1] = arr[x];
	dp[x][0] = 0;
	if (lch <= n) {
		dp[x][1] += max(0, dp[lch][1]);
		dp[x][0] = max(dp[x][0], max(dp[lch][1], dp[lch][0]));
	}
	if (rch <= n) {
		dp[x][1] += max(0, dp[rch][1]);
		dp[x][0] = max(dp[x][0], max(dp[rch][1], dp[rch][0]));
	}
	update(x >> 1);
}

int ans[MAXN];
int main() {
	freopen("f.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &val[i]);
			pos[val[i]] = i;
			arr[i] = 1;
		}
		dfs(1);
		memset(ans, 0, sizeof(ans));
		ans[n - 1] = 1;
		for (int i = 2; i <= n; i++) {
			arr[pos[i - 1]] = -1;
			update(pos[i - 1]);
			int t = max(dp[1][1], dp[1][0]);
			ans[t - 1] = max(ans[t - 1], i);
		}
		for (int i = n - 2; i >= 0; i--)
			ans[i] = max(ans[i], ans[i + 1]);
		for (int i = 0; i < n; i++)
			printf("%d%c", ans[i], " \n"[i == n - 1]);
	}


	return 0;
}
