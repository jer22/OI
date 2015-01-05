#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
vector<Edge> edges[10005];
int dp[10005][3];
void dfs(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs(e.to, x);
		if (dp[e.to][0] + e.v > dp[x][0]) {
			dp[x][1] = dp[x][0];
			dp[x][0] = dp[e.to][0] + e.v;
		} else if (dp[e.to][0] + e.v > dp[x][1]) {
			dp[x][1] = dp[e.to][0] + e.v;
		}
	}
}

void solve(int x, int pre) {
	int len = 0;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) {
			len = e.v;
			break;
		}
	}
	if (pre != -1) {
		dp[x][2] = dp[pre][2];
		if (dp[x][0] + len == dp[pre][0]) {
			dp[x][2] = max(dp[x][2], dp[pre][1]);
		} else {
			dp[x][2] = max(dp[x][2], dp[pre][0]);
		}
		dp[x][2] += len;
	}
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		solve(e.to, x);
	}
}

int main() {
	freopen("2196.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b;
		for (int i = 1; i <= n; i++) {
			edges[i].clear();
		}
		for (int i = 2; i <= n; i++) {
			scanf("%d %d", &a, &b);
			edges[i].push_back(Edge(a, b));
			edges[a].push_back(Edge(i, b));
		}
		memset(dp, 0, sizeof(dp));
		dfs(1, 1);
		solve(1, -1);
		for (int i = 1; i <= n; i++)
			cout << max(dp[i][0], dp[i][2]) << endl;
	}


	return 0;
}
