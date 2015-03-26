#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int from, to, v;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
	bool operator < (const Edge & e) const {
		return v < e.v;
	}
};

int n;
Edge edges[1000005];
int parent[305];
int find(int p) { if (p == parent[p]) return p; return parent[p] = find(parent[p]); }
void un(int p, int q) { parent[find(p)] = find(q); }
int main() {
	freopen("1601.in", "r", stdin);
	scanf("%d", &n);
	int t;
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		scanf("%d", &t);
		edges[tot++] = Edge(0, i, t);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &t);
			if (i >= j) continue;
			edges[tot++] = Edge(i, j, t);
		}
	}
	int ans = 0;
	sort(edges, edges + tot);
	for (int i = 0; i < tot; i++) {
		Edge e = edges[i];
		if (find(e.from) != find(e.to)) {
			un(e.from, e.to);
			ans += e.v;
		}
	}
	cout << ans << endl;
	return 0;
}
