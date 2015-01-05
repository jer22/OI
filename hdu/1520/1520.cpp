#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
int rating[6005];
bool vis[6005];
vector<int> edges[6005];
int dp[6005][2];

void dfs(int x) {
	vis[x] = true;
	dp[x][1] = rating[x];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (vis[nex]) continue;
		dfs(nex);
		dp[x][1] += dp[nex][0];
		dp[x][0] += max(dp[nex][0], dp[nex][1]);
	}
	vis[x] = false;
}

int main() {
	freopen("1520.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &rating[i]);
			edges[i].clear();
		}
		int a, b;
		while (~scanf("%d %d", &a, &b)) {
			if (!a && !b) break;
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		memset(dp, 0, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		dfs(1);
		printf("%d\n", max(dp[1][0], dp[1][1]));
	}
	return 0;
}
