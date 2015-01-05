#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, p;
vector<int> edges[155];
int dp[155][155];
int vis[155];
int tmp[155];
void dfs(int x) {
	dp[x][0] = 1;
	dp[x][1] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs(nex);
		memset(tmp, 0x3f, sizeof(tmp));
		for (int j = p; j > 0; j--) {
			for (int t = 0; t < j; t++) {
				tmp[j] = min(dp[x][j - t] + dp[nex][t], tmp[j]);
			}
		}
		for (int j = p; j > 0; j--) dp[x][j] = tmp[j];
	}
}

int main() {
	freopen("1947.in", "r", stdin);
	while (~scanf("%d %d", &n, &p)) {
		int a, b;
		for (int i = 1; i < n; i++)
			edges[i].clear();
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			vis[b] = 1;
		}
		memset(dp, 0x3f, sizeof(dp));
		int rt;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				rt = i;
				break;
			}
		}
		dfs(rt);
		int ans = dp[rt][p];
		for (int i = 1; i <= n; ++i)
			if (dp[i][p] < ans)
				ans = dp[i][p] + 1;
		cout << ans << endl;
	}


	return 0;
}
