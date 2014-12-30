#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge{
	int from, to;
	double value;
	Edge() {}
	Edge(int a, int b, double c) : from(a), to(b), value(c) {}
};

int n, q;
vector<Edge> edges[100005];
int cnt[100005];
int vis[100005];

int dfs(int i) {
	cnt[i] = 1;
	for (int j = 0; j < edges[i].size(); j++) {
		Edge e = edges[i][j];
		if (vis[e.to]) continue;
		vis[e.to] = 1;
		cnt[i] += dfs(e.to);
	}
	return cnt[i];
}

long long C(long long a, long long b) {
	long long t;
	if (!b || a < b) return 0;
	else if (b == 1) t = a;
	else if (b == 2) t = a * (a - 1) / 2;
	else if (b == 3) t = a * (a - 1) * (a - 2) / 6;
	return t;
}

vector<Edge> tree;
int main() {
	scanf("%d", &n);
	int a, b;
	double c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %lf", &a, &b, &c);
		edges[a].push_back(Edge(a, b, c));
		edges[b].push_back(Edge(b, a, c));
		tree.push_back(Edge(a, b, c));
		tree.push_back(Edge(b, a, c));
	}
	scanf("%d", &q);
	vis[1] = 1;
	dfs(1);
	double ans = 0;
	for (int i = 0; i < tree.size(); i += 2) {
		Edge e = tree[i];
		int num = min(cnt[e.from],cnt[e.to]);
		ans += e.value * (C(num, 2)) * (C(n - num, 1)) * 2;
		ans += e.value * (C(num, 1)) * (C(n - num, 2)) * 2;
	}
	for (int i = 1; i <= q; i++) {
		scanf("%d %d", &a, &b);
		a--;
		Edge &e = tree[a << 1];
		int num = min(cnt[e.from],cnt[e.to]);
		ans -= (e.value - b) * (C(num, 2)) * (C(n - num, 1)) * 2;
		ans -= (e.value - b) * (C(num, 1)) * (C(n - num, 2)) * 2;
		e.value = b;
		printf("%.10lf\n", ans / C(n, 3));
	}
	return 0;
}
