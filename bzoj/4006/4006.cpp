#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1305;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int T, n, m, K;
vector<Edge> edges[MAXN];
int dp[MAXN][1300], stat[MAXN];
bool vis[MAXN][1300];
queue<pair<int, int> > q;
int col[MAXN], cnt[15];

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

int id[1300];
int tt[15];
bool check(int s) {
	for (int i = 0; i <= K; i++) tt[i] = 0;
	for (int i = 0; 1 << i <= s;i++) {
		if ((1 << i) & s) tt[col[id[1 << i]]]++;
	}
	for (int i = 1; i <= K; i++)
		if (tt[i] && tt[i] != cnt[i]) return false;
	return true;
}

int f[1300];
int main() {
	freopen("4006.in", "r", stdin);
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
	memset(cnt, 0, sizeof(cnt));
	memset(col, 0, sizeof(col));
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &b, &a);
		col[a] = b;
		cnt[b]++;
		stat[a] = 1 << i;
		id[1 << i] = a;
		dp[a][stat[a]] = 0;
	}
	for (int x = 0; x < 1 << K; spfa(), x++) {
		for (int i = 1; i <= n; i++) {
			for (int j = (x - 1) & x; j; j = (j - 1) & x)
				dp[i][x] = min(dp[i][x], dp[i][j | stat[i]] + dp[i][(x ^ j) | stat[i]]);
			if (dp[i][x] < 0x3f3f3f3f) {
				q.push(make_pair(i, x)), vis[i][x] = 1;
			}
		}
	}
	memset(f, 0x3f, sizeof(f));
	for (int j = 0; j < 1 << K; j++)
		for (int i = 1; i <= n; i++)
			f[j] = min(f[j], dp[i][j]);
	for (int j = 0; j < 1 << K; j++) if (check(j))
		for (int p = (j - 1) & j; p; p = (p - 1) & j) if (check(p))
			f[j] = min(f[j], f[p] + f[p ^ j]);
	printf("%d\n", f[(1 << K) - 1]);



	return 0;
}
