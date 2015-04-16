#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

int n;
vector<int> edges[10005];
int dp[10005][15];

void dfs(int x, int pre) {
	for (int i = 1; i <= 10; i++)
		dp[x][i] = i;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
		for (int i = 1; i <= 10; i++) {
			int mi = INF;
			for (int j = 1; j <= 10; j++) {
				if (i == j) continue;
				mi = min(mi, dp[nex][j]);
			}
			dp[x][i] += mi;
		}
	}
}

int main() {
	freopen("1369.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	memset(dp, 0x3f, sizeof(dp));
	dfs(1, 1);
	int ans = INF;
	for (int i = 1; i <= 10; i++)
		ans = min(ans, dp[1][i]);
	printf("%d\n", ans);

	return 0;
}
