#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[100005];
bool vis[100005];
double dp[100005];

int main() {
	freopen("4405.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		int a, b;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			edges[b].push_back(a);
		}
		memset(dp, 0, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i < edges[n].size(); i++) {
			vis[edges[n][i]] = 1;
			dp[edges[n][i]] = 0;
		}
		for (int i = n - 1; i >= 0; i--) {
			if (!vis[i]) {
				for (int j = i + 1; j <= i + 6; j++)
					dp[i] += dp[j] / 6.0;
				dp[i] += 1;
			}
			for (int j = 0; j < edges[i].size(); j++) {
				vis[edges[i][j]] = 1;
				dp[edges[i][j]] = dp[i];
			}
		}
		printf("%.4lf\n", dp[0]);
	}



	return 0;
}
