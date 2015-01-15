#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
vector<Edge> edges[10005];
int dist[10005];
int vis[10005];

void spfa() {
	queue<int> q;
	memset(dist, -1, sizeof(dist));
	memset(vis, 0 ,sizeof(vis));
	q.push(0);
	dist[0] = 0;
	vis[0] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v > dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("1949.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, c, k;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &c, &k);
			if (!k) edges[0].push_back(Edge(i, c));
			for (int j = 1; j <= k; j++) {
				scanf("%d", &a);
				edges[a].push_back(Edge(i, c));
			}
		}
		spfa();
		int ans = 0;
		for (int i = 0; i <= n; i++) {
			ans = max(ans, dist[i]);
		}
		printf("%d\n", ans);
	}

	return 0;
}
