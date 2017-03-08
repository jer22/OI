#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 500005;

int n, q;
vector<int> edges[MAXN];
int siz[MAXN], maxson[MAXN], top[MAXN], fa[MAXN];
int lst[MAXN];

void dfspre(int x, int pre) {
	siz[x] = 1;
	fa[x] = pre;
	for (auto nex : edges[x]) if (nex != pre) {
		dfspre(nex, x);
		siz[x] += siz[nex];
		if (siz[nex] > siz[maxson[x]])
			maxson[x] = nex;
	}
}

int mrk[MAXN], _num = 0;
void dfsfuck(int x, int pre, int tp) {
	top[x] = tp, mrk[x] = ++_num;
	if (maxson[x]) dfsfuck(maxson[x], x, tp);
	for (auto nex : edges[x])
		if (nex != pre && nex != maxson[x]) dfsfuck(nex, x, nex);
	lst[x] = _num;
}

int cov[MAXN << 2];

void pushdown(int rt) {
	if (~cov[rt]) {
		cov[lch] = cov[rch] = cov[rt];
		cov[rt] = -1;
	}
}

void cover(int L, int R, int c, int l, int r, int rt) {
	if (L <= l && r <= R) {
		cov[rt] = c;
		return;
	}
	int m = l + r >> 1;
	pushdown(rt);
	if (L <= m) cover(L, R, c, lson);
	if (R > m) cover(L, R, c, rson);
}

int query(int p, int l, int r, int rt) {
	if (l == r) return cov[rt];
	pushdown(rt);
	int m = l + r >> 1;
	if (p <= m) return query(p, lson);
	else return query(p, rson);
}

int main() {
	freopen("d.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	dfspre(1, 0);
	dfsfuck(1, 0, 1);
	scanf("%d", &q);
	int op, x;
	memset(cov, -1, sizeof(cov));
	cov[1] = 0;
	while (q--) {
		scanf("%d %d", &op, &x);
		if (op == 1) {
			cover(mrk[x], lst[x], 1, 1, n, 1);
		} else if (op == 2) {
			while (x) {
				cover(mrk[top[x]], mrk[x], 0, 1, n, 1);
				x = fa[top[x]];
			}
		} else {
			int ans = query(mrk[x], 1, n, 1);
			// if (ans == -1) ans = 0;
			printf("%d\n", ans);
		}
	}

	return 0;
}
