#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define T 499

using namespace std;

struct Edge{
	int from, to, cap, flow;
	Edge() {}
	Edge(int a, int b, int c, int d) : from(a), to(b), cap(c), flow(d) {}
};

int cas, n;
vector<Edge> edges;
vector<int> G[500];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap, 0));
	edges.push_back(Edge(to, from, 0, 0));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

int layer[500];
int cur[500];

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0;
	int f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a)
				break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(0, INF);
	}
	return ans;
}

int main() {
	freopen("1698.in", "r", stdin);
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		edges.clear();
		for (int i = 0; i < 499; i++) G[i].clear();
		int tmp[8], d, w, sum = 0, maxw = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= 7; j++) scanf("%d", &tmp[j]);
			scanf("%d %d", &d, &w);
			sum += d; maxw = max(w, maxw);
			addEdge(0, i, d);
			for (int j = 1; j <= 7; j++) {
				if (!tmp[j]) continue;
				for (int k = 0; k < w; k++)
					addEdge(i, k * 7 + j + n, 1);
			}
		}
		for (int j = 0; j < maxw; j++) {
			for (int i = 1; i <= 7; i++) {
				// cout << j * 7 + i + n << endl;
				addEdge(j * 7 + i + n, T, 1);
			}
		}
		int ans = dinic();
		if (ans == sum) cout << "Yes" << endl;
		else cout << "No" << endl;
	}

	return 0;
}
