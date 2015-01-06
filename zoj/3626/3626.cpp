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

int n, r, m;
int value[105];
vector<Edge> edges[105];
int dp[105][205];
void dfs(int x, int pre) {
	for (int i = 0; i <= m; i++)
		dp[x][i] = value[x];
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs(e.to, x);
		for (int j = m; j >= 0; j--) {
			for (int k = 2 * e.v; k <= j; k++) {
				dp[x][j] = max(dp[x][j], dp[x][j - k] + dp[e.to][k - 2 * e.v]);
			}
		}
	}

}

int main() {
	freopen("3626.in", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &value[i]);
		int a, b, c;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		scanf("%d %d", &r, &m);
		memset(dp, 0, sizeof(dp));
		dfs(r, 0);
		cout <<  dp[r][m] << endl;
	}


	return 0;
}
