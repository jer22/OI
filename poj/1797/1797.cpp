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

int T;
int n, m;
vector<Edge> edges[1005];
int vis[1005];
int dist[1005];

int spfa() {
	queue<int> q;
	memset(vis, 0, sizeof(vis));
	memset(dist, 0, sizeof(dist));
	q.push(1);
	vis[1] = 1;
	dist[1] = 0x3f3f3f3f;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (min(dist[cur], e.v) > dist[e.to]) {
				dist[e.to] = min(dist[cur], e.v);
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
	return dist[n];
}

int main() {
	freopen("1797.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		int a, b, c;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			edges[a].push_back(Edge(b, c));
			edges[b].push_back(Edge(a, c));
		}
		int ans = spfa();
		printf("Scenario #%d:\n%d\n\n", cas++, ans);
	}
	return 0;
}
