#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int T;
int n;
int ans = 0x3f3f3f3f;
int res;
vector<int> edges[20005];
int dp[20005];

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
	tot = max(tot, n - dp[x]);
	if (tot < ans) {
		ans = tot;
		res = x;
	}
}

int main() {
	freopen("1655.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b;
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		ans = 0x3f3f3f3f;
		dfs1(1, 0);
		dfs2(1, 0);
		cout << res << ' ' << ans << endl;
	}


	return 0;
}
