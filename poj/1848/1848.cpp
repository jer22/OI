#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>

#define INF 10000

using namespace std;

int n;
vector<int> edges[105];
int dp[105][3];

void dfs(int x, int pre) {
	int su = 0;
	bool isleaf = true;
	int arr[105];
	int top = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int son = edges[x][i];
		if (son == pre) continue;
		isleaf = false;
		dfs(son, x);
		su += dp[son][0];
		arr[top++] = son;
	}
	if (isleaf) {
		dp[x][1] = 0;
		dp[x][0] = dp[x][2] = INF;
		return;
	}
	dp[x][1] = su;
	dp[x][2] = dp[x][0] = INF;
	for (int i = 0; i < top; i++) {
		int son = arr[i];
		dp[x][2] = min(dp[x][2], su - dp[son][0] + min(dp[son][1], dp[son][2]));
		dp[x][0] = min(dp[x][0], su - dp[son][0] + dp[son][2] + 1);
	}
	
	for (int i = 0; i < top; i++) {
		int son1 = arr[i];
		for (int j = i + 1; j < top; j++) {
			int son2 = arr[j];
			dp[x][0] = min(dp[x][0],
				su - dp[son1][0] + min(dp[son1][1], dp[son1][2]) - dp[son2][0] + min(dp[son2][1], dp[son2][2]) + 1);
		}
	}

}

int main() {
	freopen("1848.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfs(1, 1);
	if (dp[1][0] < INF)
		printf("%d\n", dp[1][0]);
	else printf("-1\n");

	return 0;
}
