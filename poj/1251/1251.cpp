#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int from, to, v;
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
	bool operator < (const Edge &e) const {
		return v < e.v;
	}
};

int n;
int parent[28];
vector<Edge> edges;

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

void addEdge(int a, int b, int c) {
	edges.push_back(Edge(a, b, c));
}

int main() {
	freopen("1251.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		char x, t;
		int c, a;
		int E = 0;
		edges.clear();
		for (int i = 1; i < n; i++) {
			cin >> x >> c;
			for (int i = 1; i <= c; i++) {
				cin >> t >> a;
				E++;
				addEdge(x - 'A' + 1, t - 'A' + 1, a);
			}
		}
		for (int i = 1; i <= 26; i++)
			parent[i] = i;
		sort(edges.begin(), edges.end());
		int ans = 0;
		for (int i = 0; i < edges.size(); i++) {
			Edge e = edges[i];
			if (find(e.from) == find(e.to)) continue;
			un(e.from, e.to);
			ans += e.v;
		}
		printf("%d\n", ans);
	}
	return 0;
}
