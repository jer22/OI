#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define INF 0x7f7f7f7f
#define T (n * n + 1)

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n;
vector<Edge> edges[250005];

bool vis[250005];
int dist[250005];
int spfa() {
	memset(dist, 0x7f, sizeof(dist));
	queue<int> q;
	q.push(0);
	dist[0] = 0;
	vis[0] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		vis[current] = 0;
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
	}
	return dist[T];
}

int main() {
	freopen("2007.in", "r", stdin);
	scanf("%d", &n);
	int v;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[i].push_back(Edge(T, v));
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &v);
			edges[i * n + j].push_back(Edge((i - 1) * n + j, v));
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[0].push_back(Edge((n - 1) * n + i, v));
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[0].push_back(Edge((i - 1) * n + 1, v));
		for (int j = 1; j < n; j++) {
			scanf("%d", &v);
			edges[(i - 1) * n + j].push_back(Edge((i - 1) * n + j + 1, v));
		}
		scanf("%d", &v);
		edges[i * n].push_back(Edge(T, v));
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[T].push_back(Edge(i, v));
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &v);
			edges[(i - 1) * n + j].push_back(Edge(i * n + j, v));
		}
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[(n - 1) * n + i].push_back(Edge(0, v));
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &v);
		edges[(i - 1) * n + 1].push_back(Edge(0, v));
		for (int j = 1; j < n; j++) {
			scanf("%d", &v);
			edges[(i - 1) * n + j + 1].push_back(Edge((i - 1) * n + j, v));
		}
		scanf("%d", &v);
		edges[T].push_back(Edge(i * n, v));
	}
	int ans = spfa();
	cout << ans << endl;
	return 0;
}
