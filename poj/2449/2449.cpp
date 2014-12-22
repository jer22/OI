#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f

using namespace std;

struct Node{
	int v, dist, tot;
	Node() {}
	Node(int a, int b, int c) : v(a), dist(b), tot(c) {}
	bool operator < (const Node &n) const {
		if (tot != n.tot)
			return tot > n.tot;
		return dist < n.dist;
	}
};

struct Edge{
	int to, value;
	Edge(int a, int b) : to(a), value(b) {}
};

int V, E;
int s, t, k;
Node start;
vector<Edge> edges[1005], redges[1005];
void addEdge(int from, int to, int value) {
	edges[from].push_back(Edge(to, value));
	redges[to].push_back(Edge(from, value));
}

int dist[1005];
void spfa() {
	bool vis[1005];
	memset(vis, 0, sizeof(vis));
	memset(dist, 0x3f, sizeof(dist));
	queue<int> q;
	dist[t] = 0;
	vis[t] = 1;
	q.push(t);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < redges[cur].size(); i++) {
			Edge e = redges[cur][i];
			if (dist[cur] + e.value < dist[e.to]) {
				dist[e.to] = dist[cur] + e.value;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					q.push(e.to);
				}
			}
		}
		vis[cur] = 0;
	}
}

priority_queue<Node> q;
int spfaAstar() {
	if (dist[s] == INF) return -1;
	q.push(start);
	if (s == t) k++;
	int cnt = 0;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (cur.v == t) {
			cnt++;
			if (cnt == k) return cur.dist;
		}
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			q.push(Node(e.to, cur.dist + e.value, cur.dist + e.value + dist[e.to]));
		}
	}
	return -1;
}

int main() {
	scanf("%d %d", &V, &E);
	int a, b, c;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
	}
	scanf("%d %d %d", &s, &t, &k);
	spfa();
	start = Node(s, 0, dist[s]);
	int ans = spfaAstar();
	cout << ans << endl;
	return 0;
}
