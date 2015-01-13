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
int vis[10005];
int dist[10005];
void addEdge(int from, int to, int v) {
	edges[from].push_back(Edge(to, v));
}

int spfa(int t) {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= t; i++)
		dist[i] = -0x3f3f3f3f;
	queue<int> q;
	q.push(0);
	vis[0] = 1;
	dist[0] = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.v > dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
	return dist[t];
}

int main() {
	freopen("1716.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b;
		int s = 0, t = 0;
		for (int i = 0; i <= 10003; i++)
			edges[i].clear();
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			addEdge(a, b + 1, 2);
			t = max(t, b + 1);
		}
		for (int i = 0; i <= t; i++) {
			addEdge(i, i + 1, 0);
			addEdge(i + 1, i, -1);
		}
		int ans = spfa(t);
		printf("%d\n", ans);
	}

	return 0;
}
