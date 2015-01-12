#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <queue>

#define INF 0x3f3f3f3f
#define T 401

using namespace std;

struct Edge{
	int from, to, cap, flow;
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int n, m, k;
int tot;
map<string, int> nodes;
vector<Edge> edges;
vector<int> G[410];
void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap, 0));
	edges.push_back(Edge(to, from, 0, 0));
	int t = edges.size();
	G[from].push_back(t - 2);
	G[to].push_back(t - 1);
}

int cur[410];
int layer[410];
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge &e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int dfs(int x, int a) {
	if (a == 0 || x == T) return a;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge & e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1 && (f = dfs(e.to, min(e.cap - e.flow, a)))) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			a -= f;
			flow += f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += dfs(0, INF);
	}
	return ans;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < 405; i++)
			G[i].clear();
		edges.clear();
		nodes.clear();
		string s1, s2;
		tot = 1;
		for (int i = 1; i <= n; i++) {
			cin >> s1;
			nodes[s1] = tot++;
			addEdge(0, nodes[s1], 1);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			cin >> s1 >> s2;
			nodes[s1] = tot++;
			if (!nodes[s2]) nodes[s2] = tot++;
			addEdge(nodes[s1], T, 1);
			addEdge(nodes[s2], nodes[s1], 1);
		}
		scanf("%d", &k);
		for (int i = 1; i <= k; i++) {
			cin >> s1 >> s2;
			if (!nodes[s1]) nodes[s1] = tot++;
			if (!nodes[s2]) nodes[s2] = tot++;
			addEdge(nodes[s2], nodes[s1], INF);
		}
		int ans = dinic();
		printf("%d\n", m - ans);
	}
	return 0;
}
