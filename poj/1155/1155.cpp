#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
int num[3005];
int dp[3005][3005];
vector<Edge> edges[3005];
int tmp[3005];
void dfs(int x) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		dfs(e.to);
		for (int j = 0; j <= num[x]; j++)
			tmp[j] = dp[x][j];
		for (int j = 0; j <= num[x]; j++) {
			for (int k = 1; k <= num[e.to]; k++) {
				dp[x][k + j] = max(dp[x][k + j], tmp[j] + dp[e.to][k] - e.v);
			}
		}
		num[x] += num[e.to];
	}
}

int main() {
	freopen("1155.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int k, a, b;
		for (int i = 1; i <= n - m; i++) {
			scanf("%d", &k);
			num[i] = 0;
			for (int j = 0; j < k; j++) {
				scanf("%d %d", &a, &b);
				edges[i].push_back(Edge(a, b));
			}
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				dp[i][j] = -INF;
		for (int i = n - m + 1; i <= n; i++) {
			num[i] = 1;
			scanf("%d", &dp[i][1]);
		}
		dfs(1);
		for (int i = m; i >= 0; i--) {
			if (dp[1][i] >= 0) {
				cout << i << endl;
				break;
			}
		}
	}


	return 0;
}
