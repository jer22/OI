#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;

struct Edge{
	int from, to, v;
	Edge() {}
	Edge(int a, int b, int c) : from(a), to(b), v(c) {}
	bool operator < (const Edge &e) const {
		return v < e.v;
	}
};

int n, m, S, T;
vector<Edge> G[MAXN];
vector<Edge> edges;

void update(int &a, int &b, int x, int y) {
	int d = __gcd(x, y);
	x /= d;
	y /= d;
	// cout << (long long)b * x << endl;
	if ((long long)a * y > (long long)b * x) {
		a = x;
		b = y;
	}
}
int fa[MAXN];
int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}
void un(int a, int b) {
	fa[find(a)] = find(b);
}
int solve(int i) {
	for (int j = 1; j <= n; j++)
			fa[j] = j;
	for (int j = i; j < edges.size(); j++) {
		if (find(edges[j].from) != find(edges[j].to))
			un(edges[j].from, edges[j].to);
		if (find(S) == find(T))
			return j;
	}
	return -1;
}
int main() {
	freopen("1050.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges.push_back(Edge(a, b, c));
		// edges.push_back(Edge(b, a, c));
		G[a].push_back(Edge(a, b, c));
		G[b].push_back(Edge(b, a, c));
	}
	sort(edges.begin(), edges.end());
	scanf("%d %d", &S, &T);
	// sort(edges.begin(), edges.end());
	a = 0x3f3f3f3f, b = 1;
	for (int i = 0; i < edges.size(); i++) {
		int j = solve(i);
		if (j == -1) break;
		int k;
		for (k = 1; k <= n; k++)
			fa[k] = k;
		for (k = j; k >= i; k--) {
			if (find(edges[k].from) != find(edges[k].to))
				un(edges[k].from, edges[k].to);
			if (find(S) == find(T))
				break;
		}
		update(a, b, edges[j].v, edges[k].v);
	}
	if (a == 0x3f3f3f3f) printf("IMPOSSIBLE\n");
	else if (b == 1) printf("%d\n", a);
	else printf("%d/%d\n", a, b);

	
	return 0;
}
