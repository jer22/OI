#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Node{
	int v, dist, tot, cost;
	Node() {}
	Node(int a, int b, int c, int d) : v(a), dist(b), tot(c), cost(d) {}
	bool operator < (const Node &n) const {
		if (tot != n.tot)
			return tot > n.tot;
		return dist < n.dist;
	}
};

struct Edge{
	int to, v, cost;
	Edge(int a, int b, int c) : to(a), v(b), cost(c) {}
};

int n, m, k;
vector<Edge> edges[105];
vector<Edge> redges[105];
int dist[105];
int vis[105];
void spfa() {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	vis[n] = 1;
	dist[n] = 0;
	q.push(n);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < redges[current].size(); i++) {
			Edge e = redges[current][i];
			if (dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[current] = 0;
	}
}

priority_queue<Node> q;
int spfaAstar() {
	while (!q.empty()) q.pop();
	if (dist[1] == 0x3f3f3f3f) return -1;
	Node start = Node(1, 0, dist[1], 0);
	q.push(start);
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (cur.v == n) {
			if (cur.cost <= k) return cur.dist;
		}
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			if (cur.cost + e.cost > k) continue;
			q.push(Node(e.to, cur.dist + e.v, cur.dist + e.v + dist[e.to], cur.cost + e.cost));
		}
	}
	return -1;
}

int main() {
	while (~scanf("%d %d %d", &k, &n, &m)) {
		int a, b, c, d;
		for (int i = 0; i <= n; i++) {
			edges[i].clear();
			redges[i].clear();
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			edges[a].push_back(Edge(b, c, d));
			redges[b].push_back(Edge(a, c, d));
		}
		spfa();
		int ans = spfaAstar();
		printf("%d\n", ans);
	}
	return 0;
}
