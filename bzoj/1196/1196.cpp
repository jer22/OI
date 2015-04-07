#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k, m;
struct Edge{
	int from, to, v1, v2;
	bool operator < (const Edge &e) const {
		return v1 < e.v1;
	}
}edges[20005];
int fa[10005];
int find(int p) {return (p == fa[p]) ? p : fa[p] = find(fa[p]); }
void un(int p, int q) { fa[find(p)] = find(q); }

bool check(int x) {
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	int tot = 0, cntv = 0;
	for (int i = 0; i < m; i++) {
		Edge e = edges[i];
		if (find(e.from) == find(e.to)) continue;
		if (e.v1 > x && e.v2 > x) continue;
		tot++;
		un(e.from, e.to);
		if (e.v1 <= x) cntv++;
	}
	if (tot < n - 1) return false;
	if (cntv < k) return false;
	return true;
}

int solve() {
	int l = 0, r = edges[m - 1].v1;
	while (l < r) {
		int mid = l + r >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	return l;
}

int main() {
	freopen("1196.in", "r", stdin);
	scanf("%d %d %d", &n, &k, &m);
	int a, b, c;
	for (int i = 0; i < m; i++)
		scanf("%d %d %d %d", &edges[i].from, &edges[i].to, &edges[i].v1, &edges[i].v2);
	sort(edges, edges + m);
	int ans = solve();

	printf("%d\n", ans);
	return 0;
}
