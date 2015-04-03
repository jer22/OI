#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int INF = 100000000;

int n;
vector<int> edges[MAXN];
int dp[MAXN][3];

void dfs(int x, int pre) {
	dp[x][0] = 1;
	dp[x][1] = INF;
	int sum = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int son = edges[x][i];
		if (son == pre) continue;
		dfs(son, x);
		dp[x][0] += min(dp[son][0], min(dp[son][1], dp[son][2]));
		dp[x][2] += dp[son][1];
		sum += min(dp[son][0], dp[son][1]);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		int son = edges[x][i];
		if (son == pre) continue;
		dp[x][1] = min(dp[x][1], dp[son][0] + sum - min(dp[son][0], dp[son][1]));
	}
}

int main() {
	freopen("1596.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 0);
	printf("%d\n", min(dp[1][0], dp[1][1]));

	return 0;
}
