#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;

int T, n;
vector<int> edges[MAXN];
int dp[MAXN];
bool f[MAXN];

void dfs(int x, int pre) {
	dp[x] = 1;
	f[x] = 0;
	int cnt = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs(nex, x);
		if (!f[nex]) cnt++;
		dp[x] += dp[nex];
	}
	if (cnt == 1) dp[x]--;
	else if (cnt >= 2) dp[x] -= 2, f[x] = 1;
}

int main() {
	freopen("1907.in", "r", stdin);
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
		dfs(1, 1);
		printf("%d\n", dp[1]);
	}


	return 0;
}
