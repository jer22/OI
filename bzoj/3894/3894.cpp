#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define P(i, j) (((i) - 1) * m + (j))
#define S 0
#define T (n * m * 3 + 1)
#define INF 0x3f3f3f3f
#define MAXN 30005

using namespace std;

int n, m, tot;
int dir[5][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {0, 0}};
struct Edge{ int v, flow, next; } edges[1000005];
int head[MAXN], cnt = 0;
int cur[MAXN], layer[MAXN], q[MAXN];

void insert(int u, int v, int cap) {
	edges[cnt] = (Edge){ v, cap, head[u] }, head[u] = cnt++;
	edges[cnt] = (Edge){ u, 0, head[v] }, head[v] = cnt++;
}

bool build() {
	int h = 1, t = 1;
	memset(layer, -1, sizeof(layer));
	layer[q[1] = S] = 0;
	while (h <= t) {
		int u = q[h++];
		for (int i = head[u]; i != -1; i = edges[i].next) {
			int v = edges[i].v;
			if (edges[i].flow && layer[v] == -1) {
				layer[v] = layer[u] + 1;
				q[++t] = v;
			}
		}
	}
	return layer[T] != -1;
}

int find(int u, int a) {
	if (u == T) return a;
	int flow = 0, f;
	for (int i = cur[u]; a && i != -1; i = edges[i].next) {
		int v = edges[i].v;
		if (edges[i].flow && layer[v] == layer[u] + 1 && (f = find(v, min(a, edges[i].flow))) > 0) {
			edges[i].flow -= f;
			edges[i ^ 1].flow += f;
			flow += f;
			a -= f;
			if (edges[i].flow) cur[u] = i;
		}
	}
	if (!flow) layer[u] = -1;
	return flow;
}

int dinic() {
	int ans = 0;
	while (build()) {
		memcpy(cur, head, sizeof(head));
		ans += find(S, INF);
	}
	return ans;
}

int main() {
	freopen("3894.in", "r", stdin);
	scanf("%d %d", &n, &m);
	memset(head, -1, sizeof(head));
	int t;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			tot += t;
			insert(S, P(i, j), t);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			tot += t;
			insert(P(i, j), T, t);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			tot += t;
			for (int k = 0; k < 5; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
				insert(P(i, j) + n * m, P(nx, ny), INF);
			}
			insert(S, P(i, j) + n * m, t);
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &t);
			tot += t;
			for (int k = 0; k < 5; k++) {
				int nx = i + dir[k][0], ny = j + dir[k][1];
				if (nx <= 0 || nx > n || ny <= 0 || ny > m) continue;
				insert(P(nx, ny), P(i, j) + n * m * 2, INF);
			}
			insert(P(i, j) + n * m * 2, T, t);
		}
	}
	tot -= dinic();
	printf("%d\n", tot);

	return 0;
}
