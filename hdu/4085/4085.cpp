#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int T, n, m, K;
vector<Edge> edges[55];
int dp[55][1300], stat[55];
bool vis[55][1300];
queue<pair<int, int> > q;

void spfa() {
	while (!q.empty()) {
		pair<int, int> cur = q.front();
		q.pop();
		int x = cur.first, st = cur.second;
		vis[x][st] = 0;
		for (int i = 0; i < edges[x].size(); i++) {
			Edge e = edges[x][i];
			if (dp[x][st] + e.v < dp[e.to][st | stat[e.to]]) {
				dp[e.to][st | stat[e.to]] = dp[x][st] + e.v;
				if (!(st & stat[e.to]) && !vis[e.to][st])
					q.push(make_pair(e.to, st)), vis[e.to][st] = 1;
			}
		}
	}
}

bool check(int s) {
	int ans = 0;
	for (int i = 0; s; s >>= 1, i++)
		if (s & 1) ans += i < K ? 1 : -1;
	return !ans;

}

int f[1300];
int main() {
	freopen("4085.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &K);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		memset(dp, 0x3f, sizeof(dp));
		memset(vis, 0, sizeof(vis));
		memset(stat, 0, sizeof(stat));
		for (int i = 1; i <= K; i++) {
			stat[i] = 1 << (i - 1);
			dp[i][stat[i]] = 0;
			stat[n - i + 1] = 1 << (K + i - 1);
			dp[n - i + 1][stat[n - i + 1]] = 0;
		}
		for (int x = 0; x < 1 << (K << 1); spfa(), x++) {
			for (int i = 1; i <= n; i++) {
				for (int j = (x - 1) & x; j; j = (j - 1) & x)
					dp[i][x] = min(dp[i][x], dp[i][j | stat[i]] + dp[i][(x ^ j) | stat[i]]);
				if (dp[i][x] < 0x3f3f3f3f) q.push(make_pair(i, x)), vis[i][x] = 1;
			}
		}
		memset(f, 0x3f, sizeof(f));
		for (int j = 0; j < 1 << (K << 1); j++)
			for (int i = 1; i <= n; i++) f[j] = min(f[j], dp[i][j]);
		for (int j = 0; j < 1 << (K << 1); j++) if (check(j))
			for (int p = (j - 1) & j; p; p = (p - 1) & j) if (check(p))
				f[j] = min(f[j], f[p] + f[p ^ j]);
		if (f[(1 << (K << 1)) - 1] == 0x3f3f3f3f) printf("No solution\n");
		else printf("%d\n", f[(1 << (K << 1)) - 1]);

	}


	return 0;
}
