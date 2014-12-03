/*
ID:shijiey1
LANG:C++
PROG:milk6
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF ((long long)((long long)1 << 62))

using namespace std;

struct Edge{
	int from, to, idx;
	long long cap, flow;
};

int V, E;
vector<Edge> edges;
vector<int> G[35];
void addEdge(int from, int to, long long cap, int n) {
	Edge e;
	e.from = from;
	e.to = to;
	e.cap = cap;
	e.flow = 0;
	e.idx = n;
	edges.push_back(e);
	e.from = to;
	e.to = from;
	e.cap = 0;
	edges.push_back(e);
	int t = edges.size();
	G[from].push_back(t - 2);
	G[to].push_back(t - 1);
}

int cur[35];

int layer[35];
int done[35];
bool build() {
	memset(layer, -1, sizeof(layer));
	memset(done, 0, sizeof(done));
	queue<int> q;
	layer[1] = 0;
	done[1] = 1;
	q.push(1);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < G[v].size(); i++) {
			Edge e = edges[G[v][i]];
			if (!done[e.to] && e.cap > e.flow) {
				layer[e.to] = layer[v] + 1;
				done[e.to] = 1;
				q.push(e.to);
			}
		}
	}
	return layer[V] != -1;
}

long long find(int x, long long a) {
	if (x == V || !a) return a;
	long long flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(a, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

long long dinic() {
	long long ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(1, INF);
	}
	return ans;
}

int main() {
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);
	scanf("%d %d", &V, &E);
	int a, b;
	long long c;
	for (int i = 1; i <= E; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		addEdge(a, b, 500000 + i - 1 + 500000 * 1001 * c, i);
	}
	long long ans = dinic();
	printf("%lld %lld\n", ans / 1001 / 500000, (ans%(500000*1001))/500000);
	int l = edges.size();
	for (int i = 0; i < l; i++) {
		Edge e = edges[i];
		if (!e.cap) continue;
		// if (e.cap != e.flow) continue;
		if (done[e.from] && !done[e.to])
		printf("%d\n", e.idx);
	}

	return 0;
}
