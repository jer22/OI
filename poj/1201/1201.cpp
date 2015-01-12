#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int to, v;
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
int dist[50005];
vector<Edge> edges[50005];
int vis[50005];
void addEdge(int from, int to, int v) {
	edges[from].push_back(Edge(to, v));
}

int spfa(int s, int t) {
	for (int i = s; i <= t; i++)
		dist[i] = -INF;
	memset(vis, 0, sizeof(vis));
	queue<int> q;
	q.push(s);
	dist[s] = 0;
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
	freopen("1201.in", "r", stdin);
	while (~scanf("%d", &n)) {
		int a, b, c;
		int s = INF, t = -INF;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			s = min(s, a - 1);
			t = max(t, b);
			addEdge(a - 1, b, c);
		}
		for (int i = s; i < t; i++) {
			addEdge(i, i + 1, 0);
			addEdge(i + 1, i, -1);
		}
		int ans = spfa(s, t);
		printf("%d\n", ans);
	}
	return 0;
}
