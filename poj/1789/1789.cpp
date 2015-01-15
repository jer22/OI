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
char str[2005][8];
int parent[2005];
vector<Edge> edges;

int find(int p) {
	if (p == parent[p]) return p;
	return parent[p] = find(parent[p]);
}

void un(int p, int q) {
	parent[find(p)] = find(q);
}

int kruskal() {
	int siz = edges.size();
	int ans = 0;
	for (int i = 0; i < siz; i++) {
		Edge e = edges[i];
		if (find(e.from) != find(e.to)) {
			un(e.from, e.to);
			ans += e.v;
		}
	}
	return ans;
}

int main() {
	freopen("1789.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i <= n; i++)
			parent[i] = i;
		edges.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s", str[i]);
			for (int j = 0; j < i; j++) {
				int v = 0;
				for (int k = 0; k < 7; k++)
					if (str[i][k] != str[j][k]) v++;
				edges.push_back(Edge(i, j, v));
			}
		}
		sort(edges.begin(), edges.end());
		int ans = kruskal();
		printf("The highest possible quality is 1/%d.\n", ans);
	}
	return 0;
}
