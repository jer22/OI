#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 505
#define S 0
#define T 1

using namespace std;

struct Edge{
	int to;
	int cap;
	Edge() {}
	Edge(int a, int b) : to(a), cap(b) {}
};

vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	G[from].push_back(edges.size() - 2);
	G[to].push_back(edges.size() - 1);
}

bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int a) {
	if (x == T || a == 0) return a;
	int flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

int dinic() {
	int flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(S, INF);
	}
	return flow;
}

int cases;
int h[MAXN];
int n, m, k;
int es[505 * 505][2];

void rebuild(int x) {
	for (int i = 0; i <= n; i++)
		G[i].clear();
	edges.clear();
	for (int i = 0; i < k; i++) {
		addEdge(0, h[i], 1);
	}
	for (int i = 0; i < m; i++) {
		addEdge(es[i][0], es[i][1], x);
		addEdge(es[i][1], es[i][0], x);
	}
}

int main() {
	freopen("h.in", "r", stdin);
	scanf("%d", &cases);
	while (cases--) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < k; i++) {
			scanf("%d", &h[i]);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &es[i][0], &es[i][1]);
		}
		if (k == 0) {
			printf("0\n");
			continue;
		}
		int l = 1, r = k;
		while (l < r) {
			int mid = l + r >> 1;
			rebuild(mid);
			int ans = dinic();
			// if (mid == 1) cout << ans << endl;
			if (ans == k) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}


	return 0;
}
