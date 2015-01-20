#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define T (n << 1 | 1)

using namespace std;

const long long INF = 1e16;

struct Edge{
	int from, to, cap;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), cap(c) {}
};

int n, m;
int sum;
long long arr[405][405];
int cow[405];
int cap[405];
vector<Edge> edges;
vector<int> G[405];

void floyd() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) 
				arr[i][j] = min(arr[i][j], arr[i][k] + arr[k][j]);
}

void addEdge(int from, int to, int cap) {
	edges.push_back(Edge(from, to, cap));
	edges.push_back(Edge(to, from, 0));
	int siz = edges.size();
	G[from].push_back(siz - 2);
	G[to].push_back(siz - 1);
}

int cur[405];
int layer[405];
bool build() {
	queue<int> q;
	memset(layer, -1, sizeof(layer));
	q.push(0);
	layer[0] = 0;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < G[current].size(); i++) {
			Edge e = edges[G[current][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[current] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

int find(int x, int curFlow) {
	if (x == T || !curFlow) return curFlow;
	int flow = 0, f;
	for (int &i = cur[x]; i < G[x].size(); i++) {
		Edge &e = edges[G[x][i]];
		if (layer[e.to] == layer[x] + 1
			&& (f = find(e.to, min(curFlow, e.cap)))) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			curFlow -= f;
			if (!curFlow) break;
		}
	}
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(0, 0x3f3f3f3f);
	}
	return ans;
}

void buildGraph(long long x) {
	for (int i = 0; i <= T; i++)
		G[i].clear();
	edges.clear();
	for (int i = 1; i <= n; i++) {
		addEdge(0, i, cow[i]);
		addEdge(i + n, T, cap[i]);
		addEdge(i, i + n, 0x3f3f3f3f);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (arr[i][j] <= x) {
				addEdge(i, j + n, 0x3f3f3f3f);
				addEdge(j, i + n, 0x3f3f3f3f);
			}
		}
	}
}

long long solve() {
	long long ans = -1;
	long long l = 0, r = INF - 1;
	while (l <= r) {
		long long mid = l + r >> 1;
		buildGraph(mid);
		if (dinic() >= sum) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return ans;
}

int main() {
	freopen("2391.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &cow[i], &cap[i]);
			sum += cow[i];
		}
		int a, b, c;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				arr[i][j] = INF;
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			if (c < arr[a][b]) arr[a][b] = arr[b][a] = c;
		}
		floyd();
		long long ans = solve();
		printf("%lld\n", ans);
	}

	return 0;
}
