#pragma comment(linker, "/STACK:102400000,102400000")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 100005;

int n, q;
int value[MAXN];
vector<int> edges[MAXN];
int tot = 0;
int siz[MAXN], deep[MAXN], max_son[MAXN];
int mark[MAXN], top[MAXN];
int fa[MAXN];

void dfs_size(int x, int dep) {

	deep[x] = dep;
	max_son[x] = 0;
	siz[x] = 1;

	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x]) continue;
		fa[nex] = x;
		dfs_size(nex, dep + 1);

		siz[x] += siz[nex];
		if (!max_son[x] || siz[nex] > siz[max_son[x]])
			max_son[x] = nex;
	}
}

int _num = 0;
void dfs_remark(int x, int topx) {
	top[x] = topx;
	mark[x] = ++_num;
	if (max_son[x]) dfs_remark(max_son[x], topx);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == fa[x]) continue;
		if (max_son[x] != nex)
			dfs_remark(nex, nex);
	}

}

int sum[MAXN << 2];
void push_up(int rt) { sum[rt] = sum[lch] ^ sum[rch]; }
void build_tree(int l, int r, int rt) {
	int mid = l + r >> 1;
	sum[rt] = 0;
	if (l == r) return;
	build_tree(lson);
	build_tree(rson);
}
void insert(int l, int r, int rt, int id, int val) {
	if (l == r) {
		sum[rt] = val;
		return;
	}
	int mid = l + r >> 1;
	if (id <= mid) insert(lson, id, val);
	else insert(rson, id, val);
	push_up(rt);
}

int query(int l, int r, int rt, int L, int R) {
	if (L <= l && R >= r)
		return sum[rt];
	int mid = l + r >> 1;
	int sum = 0;
	if (L <= mid) {
		sum ^= query(lson, L, R);
	}
	if (mid < R) {
		sum ^= query(rson, L, R);
	}
	return sum;
}

int solve(int a, int b) {
	int f1 = top[a], f2 = top[b];
	int ans = 0;
	while (f1 != f2) {
		if (deep[f1] < deep[f2]) {
			swap(f1, f2);
			swap(a, b);
		}
		ans ^= query(1, n, 1, mark[f1], mark[a]);
		a = fa[f1];
		f1 = top[a];
	}
	if (deep[a] > deep[b]) swap(a, b);
	return ans ^ query(1, n, 1, mark[a], mark[b]);
}

int T;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		int a, b;
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		tot = _num = 0;

		for (int i = 1; i < n; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			edges[b].push_back(a);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &value[i]);
			value[i]++;
		}
		dfs_size(1, 1);
		dfs_remark(1, 1);
		build_tree(1, n, 1);
		for (int i = 1; i <= n; i++) insert(1, n, 1, mark[i], value[i]);
		int op, x, y;
		for (int i = 0; i < q; i++) {
			scanf("%d", &op);
			scanf("%d %d", &x, &y);
			if (!op) {
				y++;
				insert(1, n, 1, mark[x], y);
			} else {
				int ans = solve(x, y);
				cout << ans - 1 << endl;
			}
		}
	}
	return 0;
}

