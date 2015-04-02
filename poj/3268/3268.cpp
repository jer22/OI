#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, S;
vector<Edge> edges[1005];
vector<Edge> redges[1005];

int dist1[1005];
int dist2[1005];
bool vis[1005];
struct Node{
	int v, dist;
	Node() {}
	Node(int a, int b) : v(a), dist(b) {}
	bool operator < (const Node &n) const {
		return n.dist < dist;
	}
};

void dij1() {
	priority_queue<Node> q;
	memset(dist1, 0x3f, sizeof(dist1));
	memset(vis, false, sizeof(vis));
	dist1[S] = 0;
	q.push(Node(S, 0));
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (vis[cur.v]) continue;
		vis[cur.v] = 1;
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			if (dist1[cur.v] + e.v < dist1[e.to]) {
				dist1[e.to] = dist1[cur.v] + e.v;
				q.push(Node(e.to, dist1[e.to]));
			}
		}
	}
}

void dij2() {
	priority_queue<Node> q;
	memset(dist2, 0x3f, sizeof(dist2));
	memset(vis, false, sizeof(vis));
	dist2[S] = 0;
	q.push(Node(S, 0));
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (vis[cur.v]) continue;
		vis[cur.v] = 1;
		for (int i = 0; i < redges[cur.v].size(); i++) {
			Edge e = redges[cur.v][i];
			if (dist2[cur.v] + e.v < dist2[e.to]) {
				dist2[e.to] = dist2[cur.v] + e.v;
				q.push(Node(e.to, dist2[e.to]));
			}
		}
	}
}

int main() {
	freopen("3268.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &S);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		redges[b].push_back(Edge(a, c));
	}
	dij1();
	dij2();
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (dist1[i] == 0x3f3f3f3f || dist2[i] == 0x3f3f3f3f) continue;
		ans = max(ans, dist1[i] + dist2[i]);
	}
	cout << ans << endl;
	return 0;
}
