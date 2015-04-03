#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n;
long long sum = 0;
long long siz[MAXN];
long long tot[MAXN];
vector<Edge> edges[MAXN];

void dfs1(int x, int pre) {
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs1(e.to, x);
		siz[x] += siz[e.to];
		tot[x] += tot[e.to] + siz[e.to] * e.v;
	}
}

void dfs2(int x, int pre, long long v) {
	if (x != 1)
		tot[x] = tot[pre] - siz[x] * v + (sum - siz[x]) * v;
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		dfs2(e.to, x, e.v);
	}
}

int main() {
	freopen("1827.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &siz[i]);
		sum += siz[i];
	}
	int a, b;
	long long c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	dfs1(1, 0);
	dfs2(1, 0, 0);
	long long ans = 1000000000000000000;
	for (int i = 1; i <= n; i++)
		ans = min(ans, tot[i]);
	printf("%lld\n", ans);
	return 0;
}
