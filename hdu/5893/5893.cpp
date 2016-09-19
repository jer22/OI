#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 40005;
const int INF = 0x3f3f3f3f;

int n, q;
vector<int> edges[MAXN];
int e[MAXN][3];

int fa[MAXN], siz[MAXN], dep[MAXN], son[MAXN];
int ver[MAXN << 1], first[MAXN], tot;
int ST[MAXN << 1][20];

void dfs_size(int x, int pre, int d) {
	ver[++tot] = x;
	first[x] = tot;

	siz[x] = 1;
	dep[x] = d;
	fa[x] = pre;
	son[x] = -1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex == pre) continue;
		dfs_size(nex, x, d + 1);
		ver[++tot] = x;
		siz[x] += siz[nex];
		if (son[x] == -1 || siz[nex] > siz[son[x]])
			son[x] = nex;
	}
}
int __num = 0;
int pos[MAXN], top[MAXN];
void dfs_pos(int x, int tpx) {
	top[x] = tpx;
	pos[x] = ++__num;
	if (son[x] != -1)
		dfs_pos(son[x], tpx);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != fa[x] && nex != son[x])
			dfs_pos(nex, nex);
	}
}
void RMQ() {
	for (int i = 1; i <= tot; i++)
		ST[i][0] = ver[i];
	for (int j = 1; (1 << j) <= tot; j++) {
		for (int i = 1; i + (1 << j) - 1 < tot; i++) {
			int a = ST[i][j - 1], b = ST[i + (1 << j - 1)][j - 1];
			ST[i][j] = dep[a] < dep[b] ? a : b;
		}
	}
}
int LCA(int a, int b) {
	int x = first[a], y = first[b];
	if (x > y) swap(x, y);
	int k = int(log(y - x + 1) / log(2));
	int l = ST[x][k], r = ST[y - (1 << k) + 1][k];
	int res = dep[l] < dep[r] ? l : r;
	return res;
}

int val[MAXN << 2];
int ll[MAXN << 2], rr[MAXN << 2], num[MAXN << 2];
int cover[MAXN << 2];
void pushup(int rt) {
	ll[rt] = ll[lch];
	rr[rt] = rr[rch];
	num[rt] = num[lch] + num[rch];
	if (rr[lch] == ll[rch]) num[rt]--;
}
void pushdown(int rt) {
	if (cover[rt] != -INF) {
		cover[lch] = cover[rt];
		ll[lch] = rr[lch] = cover[rt];
		num[lch] = 1;

		cover[rch] = cover[rt];
		ll[rch] = rr[rch] = cover[rt];
		num[rch] = 1;
		cover[rt] = -INF;
	}
}
void build(int l, int r, int rt) {
	cover[rt] = -INF;
	if (l == r) {
		ll[rt] = rr[rt] = val[l];
		num[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

struct Node{
	int ll, rr, num;
	Node() {}
	Node(int a, int b, int c) : ll(a), rr(b), num(c) {}
};

Node query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) {
		return Node(ll[rt], rr[rt], num[rt]);
	}
	int m = l + r >> 1;
	pushdown(rt);
	Node ans = Node(-INF, -INF, -INF);
	if (L <= m) ans = query(lson, L, R);
	if (R > m) {
		Node t = query(rson, L, R);
		if (ans.num == -INF) ans = t;
		else {
			ans.num += t.num;
			if (t.ll == ans.rr) ans.num--;
			ans.rr = t.rr;
		}
	}
	return ans;
}

int solve(int a, int b) {
	int lca = LCA(a, b);
	Node ansa = Node(-INF, -INF, 0);
	Node ansb = Node(-INF, -INF, 0);
	while (top[a] != top[lca]) {

		Node t = query(2, n, 1, pos[top[a]], pos[a]);
		if (ansa.ll == -INF) ansa = t;
		else {
			ansa.num += t.num;
			if (t.rr == ansa.ll) ansa.num--;
			ansa.ll = t.ll;
		}
		a = fa[top[a]];
	}
	while (top[b] != top[lca]) {
		Node t = query(2, n, 1, pos[top[b]], pos[b]);
		if (ansb.ll == -INF) ansb = t;
		else {
			ansb.num += t.num;
			if (t.rr == ansb.ll) ansb.num--;
			ansb.ll = t.ll;
		}
		b = fa[top[b]];
	}
	if (a == b) {
		int ans = ansa.num + ansb.num;
		if (ansa.ll == ansb.ll) ans--;
		return ans;
	}
	if (dep[a] > dep[b]) swap(a, b), swap(ansa, ansb);
	Node ansc = query(2, n, 1, pos[a] + 1, pos[b]);
	int ans = ansa.num + ansc.num + ansb.num;
	if (ansa.ll == ansc.ll) ans--;
	if (ansc.rr == ansb.ll) ans--;
	return ans;
}

void update(int l, int r, int rt, int L, int R, int c) {
	if (L <= l && r <= R) {
		ll[rt] = rr[rt] = cover[rt] = c;
		num[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	pushdown(rt);
	if (L <= m) update(lson, L, R, c);
	if (R > m) update(rson, L, R, c);
	pushup(rt);
}

void cov(int a, int b, int c) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		update(2, n, 1, pos[top[a]], pos[a], c);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) swap(a, b);
	if (a != b) update(2, n, 1, pos[a] + 1, pos[b], c);
}

int main() {
	freopen("5893.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		for (int i = 1; i <= n; i++)
			edges[i].clear();
		for (int i = 1; i < n; i++) {
			scanf("%d %d %d", &e[i][0], &e[i][1], &e[i][2]);
			edges[e[i][0]].push_back(e[i][1]);
			edges[e[i][1]].push_back(e[i][0]);
		}

		tot = 0;
		dfs_size(1, 1, 1);
		RMQ();
		__num = 0;
		dfs_pos(1, 1);
		for (int i = 1; i < n; i++) {
			if (dep[e[i][0]] < dep[e[i][1]]) swap(e[i][0], e[i][1]);
			val[pos[e[i][0]]] = e[i][2];
		}
		build(2, n, 1);
		char op[10];
		int a, b, c;
		while (q--) {
			scanf("%s", op);
			scanf("%d %d", &a, &b);
			if (op[0] == 'Q') {
				printf("%d\n", solve(a, b));
			} else {
				scanf("%d", &c);
				cov(a, b, c);
			}
		}
	}

	return 0;
}
