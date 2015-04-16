#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <iostream>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, K;
vector<Edge> edges[20005];
int dist[25][20005];
bool vis[20005];
int pre[20005];

void spfa(int s) {
	memset(dist[s], 0x3f, sizeof(dist[s]));
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	dist[s][s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[s][e.to] > dist[s][cur] + e.v) {
				dist[s][e.to] = dist[s][cur] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
}

int dp[1050000][25];
int main() {
	freopen("1097.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &K);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	for (int i = 1; i <= K + 1; i++)
		spfa(i);
	int x;
	scanf("%d", &x);
	for (int i = 0; i < x; i++) {
		scanf("%d %d", &a, &b);
		pre[b] |= (1 << a - 2);
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][1] = 0;
	for (int now = 0; now < 1 << K; now++) {
		for (int i = 1; i <= K + 1; i++) {
			if (dp[now][i] == INF) continue;
			for (int j = 2; j <= K + 1; j++) {
				int nex = now | (1 << j - 2);
				if ((now & pre[j]) == pre[j])
					dp[nex][j] = min(dp[nex][j], dp[now][i] + dist[i][j]);
			}
		}
	}
	int ans = INF;
	for (int i = 1; i <= K + 1; i++)
		ans = min(ans, dp[(1 << K) - 1][i] + dist[i][n]);
	cout << ans << endl;

	return 0;
}
