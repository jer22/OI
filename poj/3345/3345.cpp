#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int n, m;
map<string, int> mmap;
vector<int> edges[305];
bool vis[305];
int cost[305];
int dp[305][305];
int num[305];

void dfs(int x) {
	num[x] = 0;
	dp[x][0] = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs(nex);
		num[x] += num[nex];
		for (int j = num[x]; j >= 0; j--) {
			for (int k = 0; k <= j && k <= num[nex]; k++) {
				dp[x][j] = min(dp[x][j], dp[x][j - k] + dp[nex][k]);
			}
		}
	}
	num[x]++;
	dp[x][num[x]] = cost[x];
}

int main() {
	freopen("3345.in", "r", stdin);
	char tmp[100];
	while (gets(tmp), tmp[0] != '#') {
		sscanf(tmp, "%d %d", &n, &m);
		mmap.clear();
		memset(vis, 0, sizeof(vis));
		int tot = 1;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		string s, ss;
		int k;
		for (int i = 1; i <= n; i++) {
			cin >> s >> k;
			if (!mmap[s]) mmap[s] = tot++;
			int a = mmap[s];
			cost[a] = k;
			while (getchar() != '\n') {
				cin >> ss;
				if (!mmap[ss]) mmap[ss] = tot++;
				int b = mmap[ss];
				vis[b] = 1;
				edges[a].push_back(b);
			}
		}
		for (int i = 1; i <= n; i++)
			if (!vis[i]) edges[0].push_back(i);
		memset(dp, 0x3f, sizeof(dp));
		dfs(0);
		int ans = 0x3f3f3f3f;
		for (int i = m; i <= n; i++)
			ans = min(ans, dp[0][i]);
		cout << ans << endl;
	}

	return 0;
}
