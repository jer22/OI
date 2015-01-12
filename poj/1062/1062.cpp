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

int n, m;
int level[105];
vector<Edge> edges[105];
int dist[105];
int vis[105];
void spfa(int l, int r) {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[0] = 0;
	q.push(0);
	vis[0] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (level[e.to] < l || level[e.to] > r) continue;
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				if (!vis[e.to]) {
					q.push(e.to);
					vis[e.to] = 1;
				}
			}
		}
		vis[cur] = 0;
	}
}

int main() {
	freopen("1062.in", "r", stdin);
	while (~scanf("%d %d", &m, &n)) {
		int a, b, k;
		for (int i = 0; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &a, &b, &k);
			edges[0].push_back(Edge(i, a));
			level[i] = b;
			for (int j = 1; j <= k; j++) {
				scanf("%d %d", &a, &b);
				edges[a].push_back(Edge(i, b));
			}
		}
		int ans = 0x3f3f3f3f;
		for (int i = level[1] - m; i <= level[1]; i++) {
			spfa(i, i + m);
			ans = min(ans, dist[1]);
		}
		cout << ans << endl;
	}

	return 0;
}
