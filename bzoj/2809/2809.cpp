#include <bits/stdc++.h>

#define MAXN 100005

using namespace std;

int n, m;
vector<int> edges[MAXN];
int c[MAXN], l[MAXN];
int v[MAXN], lch[MAXN], rch[MAXN], root[MAXN];
int tot;
long long sum[MAXN], siz[MAXN];
long long ans;

int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (v[x] < v[y]) swap(x, y);
	rch[x] = merge(rch[x], y);
	swap(lch[x], rch[x]);
	return x;
}

void pop(int &x) {
	x = merge(lch[x], rch[x]);
}

int top(int x) {
	return v[x];
}

void dfs(int x) {
	root[x] = ++tot;
	v[tot] = c[x];
	siz[x] = 1;
	sum[x] = c[x];
	for (int i = 0; i < edges[x].size(); i++) {
		int to = edges[x][i];
		dfs(to);
		sum[x] += sum[to];
		siz[x] += siz[to];
		root[x] = merge(root[x], root[to]);
	}
	while (sum[x] > m) {
		sum[x] -= top(root[x]);
		pop(root[x]);
		siz[x]--;
	}
	ans = max(ans, siz[x] * l[x]);
}

int main() {
	freopen("2809.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int x;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		edges[x].push_back(i);
		scanf("%d %d", &c[i], &l[i]);
	}
	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
