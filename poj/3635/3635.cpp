#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define INF 0x3f

using namespace std;

struct Node{
	int v, gas, cost;
	Node(int a, int b, int c) : v(a), gas(b), cost(c) {}
	bool operator < (const Node &n) const {
		return cost > n.cost;
	}
};

struct Edge{
	int to, value;
	Edge(int a, int b) : to(a), value(b) {}
};

int V, E, Q;
int s, t, cap;
int price[1111];
vector<Edge> edges[1111];

void addEdge(int from, int to, int value) {
	edges[from].push_back(Edge(to, value));
}

int cost[1111][111];
bool vis[1111][111];
int spfa() {
	memset(vis, 0, sizeof(vis));
	memset(cost, 0x3f, sizeof(cost));
	cost[s][0] = 0;
	vis[s][0] = 1;
	priority_queue<Node> q;
	q.push(Node(s, 0, 0));
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		if (cur.v == t) return cur.cost;
		vis[cur.v][cur.gas] = 1;
		if (cur.gas + 1 <= cap && cur.cost + price[cur.v] < cost[cur.v][cur.gas + 1]) {
			if (!vis[cur.v][cur.gas + 1]) {
				cost[cur.v][cur.gas + 1] = cur.cost + price[cur.v];
				q.push(Node(cur.v, cur.gas + 1, cur.cost + price[cur.v]));
			}
		}
		for (int i = 0; i < edges[cur.v].size(); i++) {
			Edge e = edges[cur.v][i];
			if (cur.gas - e.value >= 0 && cur.cost < cost[e.to][cur.gas - e.value]) {
				if (!vis[e.to][cur.gas - e.value]) {
					cost[e.to][cur.gas - e.value] = cur.cost;
					q.push(Node(e.to, cur.gas - e.value, cur.cost));
				}
			}
		}
	}
	return INF;
}

int main() {
	scanf("%d %d", &V, &E);
	for (int i = 0; i < V; i++) {
		scanf("%d", &price[i]);
	}
	int a, b, c;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		scanf("%d %d %d", &cap, &s, &t);
		int ans = spfa();
		if (ans == INF) printf("impossible\n");
		else printf("%d\n", ans);
	}
	return 0;
}
