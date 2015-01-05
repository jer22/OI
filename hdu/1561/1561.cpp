#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> edges[205];
int price[205];
int dp[205][205];
int num[205];
int tmp[205];
void dfs(int x) {
	dp[x][1] = price[x];
	num[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs(nex);
		num[x] += num[nex];
		for (int j = num[x]; j >= 1; j--) {
			for (int k = 1; k + j <= num[x]; k++) {
				dp[x][j + k] = max(dp[x][j + k], dp[x][j] + dp[nex][k]);
			}
		}
	}
}

int main() {
	freopen("1561.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		int a, b;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(i);
			price[i] = b;
		}
		memset(dp, 0, sizeof(dp));
		dfs(0);
		cout << dp[0][m + 1] << endl;
	}


	return 0;
}
