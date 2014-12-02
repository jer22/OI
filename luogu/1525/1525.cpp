#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 20010
#define MAXM 100010

using namespace std;

struct Edge {
	int u, v, value;
	bool operator < (const Edge &e) const {
		return value > e.value;
	}
};

int V, E;
Edge edges[MAXM];
int parent[MAXN];
int enemy[MAXN];

int find(int p) {
	if (parent[p] == p)
		return p;
	return parent[p] = find(parent[p]);
}

int un(int p, int q) {
	int tx = find(p);
	int ty = find(q);
	if (tx == ty)
		return 0;
	parent[tx] = q;
	return 1;
}

int main() {
	freopen("1525.in", "r", stdin);
	memset(enemy, -1, sizeof(enemy));
	scanf("%d %d", &V, &E);
	for (int i = 1; i <=V; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].value);
	}
	sort(edges, edges + E);
	for (int i = 0; i < E; i++) {
		Edge e = edges[i];
		if (find(e.u) == find(e.v)) {
			printf("%d\n", e.value);
			return 0;
		}
		if (enemy[e.u] == -1) {
			enemy[e.u] = e.v;
		}
		if (enemy[e.v] == -1) {
			enemy[e.v] = e.u;
		}
		if (enemy[e.u] != -1) {
			un(enemy[e.u], e.v);
		}
		if (enemy[e.v] != -1) {
			un(enemy[e.v], e.u);
		}
	}
	printf("0\n");
	return 0;
}
