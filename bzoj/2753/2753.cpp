#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

int height[MAXN];
struct Edge{
	int from, to;
	long long v;
	Edge() {}
	Edge(int a, int b, long long c) : from(a), to(b), v(c) {}
	bool operator < (const Edge &e) const {
		if (height[to] != height[e.to]) return height[to] > height[e.to];
		return v < e.v;
	}
};

int n, m, cnt = 0;
vector<Edge> E;
int fa[MAXN];

int find(int p) { return (p == fa[p]) ? p : fa[p] = find(fa[p]); }
void un(int p, int q) { fa[find(p)] = find(q); }

bool vis[MAXN];
vector<int> edges[MAXN];
void addEdge(int a, int b, long long c) {
	E.push_back(Edge(a, b, c));
	edges[a].push_back(b);
}

void dfs(int x) {
	vis[x] = 1, cnt++;
	for (int i = 0; i < edges[x].size(); i++)
		if (!vis[edges[x][i]]) dfs(edges[x][i]);
}

int main() {
	freopen("2753.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &height[i]);
		fa[i] = i;
	}
	int a, b;
	long long c;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		if (height[a] >= height[b]) addEdge(a, b, c);
		if (height[b] >= height[a]) addEdge(b, a, c);
	}
	sort(E.begin(), E.end());
	dfs(1);
	long long ans = 0;
	for (int i = 0; i < E.size(); i++) {
		Edge e = E[i];
		if (vis[e.from] && vis[e.to] && find(e.from) != find(e.to)) {
			un(e.from, e.to);
			ans += e.v;
		}
	}
	printf("%d %lld\n", cnt, ans);

	return 0;
}
