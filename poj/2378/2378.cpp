#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> edges[10005];
vector<int> ans;
int dp[10005];
// int num[10005];
void dfs1(int x, int pre) {
	dp[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs1(nex, x);
		dp[x] += dp[nex];
	}
}

void dfs2(int x, int pre) {
	int tot = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs2(nex, x);
		tot = max(tot, dp[nex]);
	}
	if (tot <= n / 2 && n - dp[x] <= n / 2)
		ans.push_back(x);
}

int main() {
	freopen("2378.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		ans.clear();
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		dfs1(1, 0);
		dfs2(1, 0);
		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i] << endl;
		if (ans.empty())
			cout << "NONE" << endl;
	}


	return 0;
}
