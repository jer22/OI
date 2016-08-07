#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 505
#define S 0
#define T 503

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

int n, m;
int w[25], r[25], p[25][25];
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i <= n; i++)
		scanf("%d", &r[i]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &p[i][j]);
	int sum = 0;
	for(int i = 2; i <= n; i++) {
		if (w[1] + r[1] - w[i] < 0) {
			printf("NO\n");
			return 0;
		}
		addEdge(0, i, w[1] + r[1] - w[i]);
	}
	int tot = n;
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j < i; j++) {
			if (!p[i][j]) continue;
			addEdge(i, ++tot, INF);
			addEdge(j, tot, INF);
			addEdge(tot, T, p[i][j]);
			sum += p[i][j];
		}
	}
	int ans = dinic();
	if (sum <= ans) printf("YES\n");
	else printf("NO\n");


	return 0;
}
