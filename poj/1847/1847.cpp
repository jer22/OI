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

int n, s, t;
vector<Edge> edges[105];
int dist[105];
int vis[105];

int spfa() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	dist[s] = 0;
	vis[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < edges[cur].size(); i++) {
			Edge e = edges[cur][i];
			if (dist[cur] + e.v < dist[e.to]) {
				dist[e.to] = dist[cur] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
	return dist[t];
}

int main() {
	while (~scanf("%d %d %d", &n, &s, &t)) {
		int cnt, a;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &cnt);
			for (int j = 0; j < cnt; j++) {
				scanf("%d", &a);
				if (!j) edges[i].push_back(Edge(a, 0));
				else edges[i].push_back(Edge(a, 1));
			}
		}
		int ans = spfa();
		if (ans == 0x3f3f3f3f) ans = -1;
		printf("%d\n", ans);
	}
	return 0;
}
