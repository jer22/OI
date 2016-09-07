#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 300005;

int n, q;
int col[MAXN];
vector<int> edges[MAXN];
int top[MAXN], mark[MAXN], fa[MAXN], siz[MAXN], max_son[MAXN], depth[MAXN];
bitset<102> ans[MAXN << 2];

void dfs_size(int x, int dep) {
	depth[x] = dep;
	siz[x] = 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		dfs_size(nex, dep + 1);
		fa[nex] = x;
		if (siz[nex] > siz[max_son[x]]) max_son[x] = nex;
	}
}

int tot = 0;
void dfs_remark(int x, int topx) {
	top[x] = topx;
	mark[x] = ++tot;
	if (max_son[x]) dfs_remark(max_son[x], topx);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != max_son[x]) dfs_remark(nex, nex);
	}
}

void pushdown(int rt) {
	ans[lch] ^= ans[rt];
	ans[rch] ^= ans[rt];
	ans[rt].reset();
}

void update(int L, int R, int l, int r, int rt, int co) {
	if (L <= l && r <= R) {
		ans[rt][co] = ans[rt][co] ^ 1;
		return; 
	}
	pushdown(rt);
	int m = l + r >> 1;
	if (L <= m) update(L, R, lson, co);
	if (R > m) update(L, R, rson, co);
}

void solve(int i, int j, int c) {
	int x = top[i], y = top[j];
	while (x != y) {
		if (depth[x] < depth[y]) {
			swap(x, y);
			swap(i, j);
		}
		update(mark[x], mark[i], 1, n, 1, c);
		i = fa[x];
		x = top[i];
	}
	if (depth[i] < depth[j]) swap(i, j);
	update(mark[j], mark[i], 1, n, 1, c);
}

bitset<102> query(int p, int l, int r, int rt) {
	if (l == r) return ans[rt];
	pushdown(rt);
	int m = l + r >> 1;
	if (p <= m) return query(p, lson);
	else return query(p, rson);
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &col[i]);
	int a, b;
	for (int i = 2; i <= n; i++) {
		scanf("%d", &a);
		edges[a].push_back(i);
	}
	dfs_size(1, 1);
	dfs_remark(1, 1);
	for (int i = 1; i <= n; i++) {
		solve(1, i, col[i]);
	}
	// cout << query(3, 1, n, 1) << endl;

	while (q--) {
		scanf("%d %d", &a, &b);
		if (a) {
			solve(1, b, col[b]);
			solve(1, b, a);
			col[b] = a;
		} else {
			int ret = query(mark[b], 1, n, 1).count();
			printf("%d\n", ret);
		}
	}


	return 0;
}
