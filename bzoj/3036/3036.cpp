#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m;
vector<Edge> edges[MAXN];
bool vis[MAXN];
int out[MAXN];
double dp[MAXN];

void dfs(int x) {
	if (vis[x]) return;
	vis[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		dfs(e.to);
		dp[x] += dp[e.to] + (double)e.v;
	}
	if (out[x]) dp[x] /= (double)out[x];
}

int main() {
	freopen("3036.in", "r", stdin);
	cin >> n >> m;
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		out[a]++;
	}
	dfs(1);
	printf("%.2lf\n", dp[1]);


	return 0;
}
