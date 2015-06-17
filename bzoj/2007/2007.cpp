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

struct Node{
	int v, dist;
	Node() {}
	Node(int a, int b) : v(a), dist(b) {}
	bool operator < (const Node &n) const {
		return dist > n.dist;
	}
};

int n;
vector<Edge> edges[250005];

bool vis[250005];
int dist[250005];
priority_queue<Node> q;
int dij() {
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	q.push(Node(0, 0));
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			if (cur.dist + e.v < dist[e.to])
				q.push(Node(e.to, dist[e.to] = cur.dist + e.v));
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
	int ans = dij();
	printf("%d\n", ans);
	return 0;
}
