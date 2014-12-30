#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXV 1000
#define MAXE 4000

using namespace std;

struct Edge {
	int from;
	int to;
	int value;
	bool operator < (const Edge &e) const {
		return value < e.value;
	}
};

Edge edges[MAXE];
int t = 0;
void addEdge(int u, int v, int value) {
	Edge e;
	e.from = u;
	e.to = v;
	e.value = value;
	edges[t++] = e;
}

int V, E;
int parent[MAXV];

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

vector<Edge> ans;
int main() {
	scanf("%d %d", &V, &E);
	int x, y, z;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &z);
		addEdge(x, y, z);
	}
	sort(edges, edges + E);
	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < E; i++) {
		Edge e = edges[i];
		if (find(e.from) != find(e.to)) {
			ans.push_back(e);
			un(e.from, e.to);
		}
	}
	printf("\n");
	for (int i = 0; i < ans.size(); i++) {
		printf("%d %d %d\n", ans[i].from, ans[i].to, ans[i].value);
	}

	return 0;
}
