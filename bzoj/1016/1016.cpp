#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MOD 31011

using namespace std;

struct Edge{
	int from, to, v;
	bool operator < (const Edge &e) const {
		return v < e.v;
	}
};

int n, m;
Edge edges[1005];
int parent[1005];
int parent2[1005];

int find(int x) {
	if (x == parent[x]) return x;
	return parent[x] = find(parent[x]);
}

int find2(int x) {
	if (x == parent2[x]) return x;
	return find2(parent2[x]);
}

int dfs(int l, int r, int num) {
	if (!num) return 1;
	if (r < l) return 0;
	int ans = dfs(l + 1, r, num);
	int p = find2(edges[l].from);
	int q = find2(edges[l].to);
	if (p != q) {
		parent2[p] = q;
		ans += dfs(l + 1, r, num - 1);
		parent2[p] = p;
	}
	return ans;
}

int main() {
	freopen("1016.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		parent[i] = parent2[i] = i;
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d", &edges[i].from, &edges[i].to, &edges[i].v);
	sort(edges + 1, edges + m + 1);
	int tot = 0, sum = 0;
	int before = 0;
	int l = 0, r;
	int ans = 1;
	for (int i = 1; i <= m + 1; i++) {
		if (edges[i].v != before) {
			before = edges[i].v;
			r = i - 1;
			if (i != 1) ans = (ans * dfs(l, r, sum) % MOD);
			sum = 0;
			l = i;
			memcpy(parent2, parent, sizeof(parent2));
		}
		int p = find(edges[i].from);
		int q = find(edges[i].to);
		if (p != q) {
			parent[p] = q;
			sum++;
			tot++;
		}
	}
	if (tot == n - 1)
		printf("%d\n", ans);
	else printf("0\n");
	return 0;
}
