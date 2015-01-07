#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 21474836470000000

using namespace std;

int n, m;
long long sum, ans;
int val[100005];
vector<int> edges[100005];
long long dp[100005];

long long rabs(long long x) {
	return x > 0 ? x : -x;
}

void dfs1(int x, int pre) {
	dp[x] = val[x];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs1(nex, x);
		dp[x] += dp[nex];
	}
}

void dfs2(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs2(nex, x);
		ans = min(ans, rabs(dp[nex] - (sum - dp[nex])));
	}
}

int main() {
	freopen("3140.in", "r", stdin);
	int cas = 1;
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		sum = 0;
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
			scanf("%d", &val[i]);
			sum += val[i];
		}
		int a, b;
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		ans = INF;
		dfs1(1, 0);
		dfs2(1, 0);
		printf("Case %d: %I64d\n", cas++, ans);
	}
	return 0;
}
