#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1505;

int n;
vector<int> edges[MAXN];
int dp[MAXN][2];

void dfs(int x, int pre) {
	dp[x][1] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
	}
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dp[x][0] += dp[nex][1];
		dp[x][1] += min(dp[nex][0], dp[nex][1]);
	}

}

int main() {
	freopen("1054.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		int t, x, a;
		for (int i = 0; i < n; i++) {
			scanf("%d", &t);
			getchar();
			getchar();
			scanf("%d", &x);
			getchar();
			for (int j = 0; j < x; j++) {
				scanf("%d", &a);
				edges[t].push_back(a);
				edges[a].push_back(t);
			}
		}
		memset(dp, 0, sizeof(dp));
		dfs(0, 0);
		cout << min(dp[0][0], dp[0][1]) << endl;
	}


	return 0;
}
