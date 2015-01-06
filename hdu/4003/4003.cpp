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

int n, s, k;
vector<Edge> edges[10005];
int dp[10005][15];
void dfs(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs(e.to, x);
		for (int j = k; j >= 0; j--) {
			dp[x][j] += dp[e.to][0] + (e.v << 1);
			for (int t = 1; t <= j; t++) {
				dp[x][j] = min(dp[x][j], dp[x][j - t] + dp[e.to][t] + e.v * t);
			}
		}
	}

}

int main() {
	freopen("4003.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &s, &k)) {
		int a, b, c;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		memset(dp, 0, sizeof(dp));
		dfs(s, 0);
		cout << dp[s][k] << endl;
	}


	return 0;
}
