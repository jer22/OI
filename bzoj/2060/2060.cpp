#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector<int> edges[50005];
int dp[50005][2];
void dfs(int x, int pre) {
	dp[x][0] = 0;
	dp[x][1] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
		dp[x][0] += max(dp[nex][0], dp[nex][1]);
		dp[x][1] += dp[nex][0];
	}
}

int main() {
	freopen("2060.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 1);
	printf("%d\n", max(dp[1][0], dp[1][1]));

	return 0;
}
