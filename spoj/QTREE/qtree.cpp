#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 10005;
const int INF = 0x3f3f3f3f;

int T;
int n;
vector<int> edges[MAXN];
int e[MAXN][3];

int fa[MAXN], siz[MAXN], dep[MAXN], son[MAXN];

void dfs_size(int x, int pre, int d) {
	siz[x] = 1;
	dep[x] = d;
	fa[x] = pre;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_size(nex, x, d + 1);
		siz[x] += siz[nex];
		if (son[x] == -1 || siz[nex] > siz[son[x]])
			son[x] = nex;
	}
}
int __num = 0;
int pos[MAXN], top[MAXN], ver[MAXN];
void dfs_pos(int x, int tpx) {
	top[x] = tpx;
	pos[x] = ++__num;
	ver[__num] = x;
	if (son[x] != -1)
		dfs_pos(son[x], tpx);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != fa[x] && nex != son[x])
			dfs_pos(nex, nex);
	}
}

int mx[MAXN << 2];
void pushup(int rt) { mx[rt] = max(mx[lch], mx[rch]); }
void build(int l, int r, int rt) {
	mx[rt] = -INF;
	if (l == r) return;
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void update(int l, int r, int rt, int p, int val) {
	if (l == r) {
		mx[rt] = val;
		return;
	}
	int m = l + r >> 1;
	if (p <= m) update(lson, p, val);
	else update(rson, p, val);
	pushup(rt);
}

int query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) return mx[rt];
	int m = l + r >> 1;
	int ans = -INF;
	if (L <= m) ans = max(ans, query(lson, L, R));
	if (R > m) ans = max(ans, query(rson, L, R));
	return ans;
}

int solve(int x, int y) {
	int ans = -INF;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) swap(x, y);
		ans = max(ans, query(2, n, 1, pos[top[x]], pos[x]));
		x = fa[top[x]];
	}
	if (dep[x] > dep[y]) swap(x, y);
	if (x != y) ans = max(ans, query(2, n, 1, pos[x] + 1, pos[y]));
	return ans;
}

int main() {
	freopen("qtree.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &e[i][0], &e[i][1], &e[i][2]);
			edges[e[i][0]].push_back(e[i][1]);
			edges[e[i][1]].push_back(e[i][0]);
		}
		memset(son, -1, sizeof(son));
		dfs_size(1, 1, 1);
		__num = 0;
		dfs_pos(1, 1);
		build(2, n, 1);
		for (int i = 1; i < n; i++) {
			if (dep[e[i][0]] > dep[e[i][1]]) swap(e[i][0], e[i][1]);
			update(2, n, 1, pos[e[i][1]], e[i][2]);
		}
		char op[10];
		int a, b;
		while (~scanf("%s", op)) {
			if (op[0] == 'D') break;
			scanf("%d %d", &a, &b);
			if (op[0] == 'C') {
				update(2, n, 1, pos[e[a][1]], b);
			} else {
				printf("%d\n", solve(a, b));
			}
		}
	}




	return 0;
}
