#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
int bugs[105], money[105];
vector<int> edges[105];
bool vis[105];
int dp[105][105];

void dfs(int x) {
	vis[x] = 1;
	int cost = (bugs[x] + 19) / 20;
	for (int i = cost; i <= m; i++)
		dp[x][i] = money[x];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (vis[nex]) continue;
		dfs(nex);
		for (int j = m; j >= cost; j--) {
			for (int k = 1; k <= m - j; k++) {
				if (dp[nex][k])
					dp[x][j + k] = max(dp[x][j + k], dp[x][j] + dp[nex][k]);
			}
		}
	}
}

int main() {
	freopen("1011.in", "r", stdin);
	while (~scanf("%d %d", &n, &m), n + m > 0) {
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &bugs[i], &money[i]);
			edges[i].clear();
		}
		memset(vis, 0, sizeof(vis));
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		if (!m) {
			cout << 0 << endl;
			continue;
		}
		memset(dp, 0, sizeof(dp));
		dfs(1);
		cout << dp[1][m] << endl;
	}


	return 0;
}
