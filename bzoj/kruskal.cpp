#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXV 1000
#define MAXE 4000

using namespace std;

struct Edge {
	int u;
	int v;
	int value;
	Edge() {}
	Edge(int a, int b, int c) : u(a), v(b), value(c) {}
	bool operator < (const Edge &e) const {
		return value < e.value;
	}
};

int V, E;
int parent[MAXV]; // 并查集
Edge edges[MAXE];
vector<Edge> ans;

int find(int p) {
	if (parent[p] == p) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

int main() {
	scanf("%d %d", &V, &E);
	int x, y, z;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].value);
	}
	sort(edges, edges + E);
	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < E; i++) {
		Edge e = edges[i];
		if (find(e.u) != find(e.v)) {
			ans.push_back(e);
			un(e.u, e.v);
		}
	}
	for (int i = 0; i < ans.size(); i++) {
		printf("%d %d %d\n", ans[i].u, ans[i].v, ans[i].value);
	}
	return 0;
}
