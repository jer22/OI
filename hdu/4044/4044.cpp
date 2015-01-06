#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T;
int n, m;
int tp[1005][205];
int dp[1005][205];
vector<int> edges[1005];

void dfs(int x, int pre) {
	if (x != 1 && edges[x].size() == 1) {
		for (int i = 0; i <= m; i++)
			dp[x][i] = tp[x][i];
		return;
	}
	// for (int i = 0; i <= m; i++)
	// 	dp[x][i] = 0x3f3f3f3f;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
		for (int j = m; j >= 0; j--) {
			int t = 0;
			for (int k = 0; k <= j; k++) {
				t = max(t, min(dp[x][j - k], dp[nex][k]));
			}
			dp[x][j] = t;
		}
	}
	for (int j = m; j >= 0; j--)
		for (int k = 0; k <= j; k++)
			dp[x][j] = max(dp[x][j], dp[x][j - k] + tp[x][k]);

}

int main() {
	freopen("4044.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int a, b, k;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		memset(tp, 0, sizeof(tp));
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		scanf("%d", &m);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &k);
			for (int j = 1; j <= k; j++) {
				scanf("%d %d", &a, &b);
				tp[i][a] = max(tp[i][a], b);
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				tp[i][j] = max(tp[i][j], tp[i][j - 1]);
		dfs(1, 0);
		cout << dp[1][m] << endl;
	}


	return 0;
}
