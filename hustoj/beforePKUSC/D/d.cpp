#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int T, n, m, K;
vector<Edge> edges[52];
int dist[52][52];
int pos[10], tim[10], ftim[10], cnt[10];
vector<int> pass[10];
int dp[55][260][260];
int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &n, &m, &K);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		int a, b, c;
		memset(dist, 0x3f, sizeof(dist));
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
			dist[a][b] = dist[b][a] = c;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

		int x;
		for (int i = 0; i < K; i++) {
			pass[i].clear();
			scanf("%d %d %d %d", &pos[i], &tim[i], &ftim[i], &cnt[i]);
			for (int t = 0; t < cnt[i]; t++) {
				scanf("%d", &x);
				pass[i].push_back(x);
			}
		}
		dp[1][0] = 0;
		for (int j = 0; j < 1 << K; j++) {
			for (int i = 1; i <= n; i++) {
				if (dp[i][j] == INF) continue;
				for (int nex = 0; nex < K; nex++) {
					if (j & (1 << nex)) continue;
					int nexstat = j & (1 << nex);
					int nexpos = pos[nex];
					dp[nexpos][nexstat] = min(dp[nexpos][nexstat], dp[i][j] + dist[i][nexpos] + tim[nex]);
					for (int t = 0; t < pass[nex]; t++) {
						dp[nexpos][nexstat] = min(dp[nexpos][nexstat], dp[i][j] + dist[i][t] + dist[])
					}
				}
			}
		}
	}


	return 0;
}
