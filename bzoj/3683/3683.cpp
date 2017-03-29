#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 300005;

int n, m;
vector<int> edges[MAXN];
long long w[MAXN];

int fa[MAXN];
int siz[MAXN], son[MAXN];
long long sum[MAXN], num[MAXN];
void dfspre(int x) {
	siz[x] = 1;
	sum[x] = w[x];
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		fa[nex] = x;
		dfspre(nex);
		sum[x] += sum[nex];
		siz[x] += siz[nex];
		if (siz[nex] > siz[son[x]])
			son[x] = nex;
	}
}
int mrk[MAXN], tot = 0, ed[MAXN];
int top[MAXN];
long long poop[MAXN];

void dfsmrk(int x, int tp) {
	top[x] = tp;
	mrk[x] = ++tot;
	if (son[x]) dfsmrk(son[x], tp);
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		if (nex != son[x]) dfsmrk(nex, nex);
	}
	ed[x] = tot;
	poop[mrk[x]] += w[x] * (siz[x] - 1);
	num[mrk[x]] += siz[x] - 1;
	for (int i = 0; i < edges[x].size(); i++) {
		int nex = edges[x][i];
		poop[mrk[x]] += sum[nex] * (siz[x] - siz[nex]);
		num[mrk[x]] += (long long)(siz[x] - siz[nex]) * siz[nex];
	}
}
// void build(int l, int r, int rt) {
// 	if (l == r) {
// 		ans[rt] = poop[l];
// 		return;
// 	}
// 	int mid = l + r >> 1;
// 	build(l, mid, rt << 1);
// 	build(mid + 1, r, rt << 1 | 1);
// }
long long del[MAXN << 2], del2[MAXN << 2];
void pushdown(int l, int r, int rt) {
	if (l == r) {
		poop[l] += del[rt] * (siz[l] - siz[son[l]]);
		// poop[r] += del[rt] * (siz[r] - siz[son[r]]);

		poop[l] += num[l] * del2[rt];
		// poop[r] += num[r] * del2[rt];
		del[rt] = del2[rt] = 0;
		return;
	}
	int mid = l + r >> 1;
	del[lch] += del[rt];
	del[rch] += del[rt];
	del[rt] = 0;

	del2[lch] += del2[rt];
	del2[rch] += del2[rt];
	del2[rt] = 0;
}
long long query(int l, int r, int rt, int p) {
	pushdown(l, r, rt);
	if (l == r) return poop[l];
	int mid = l + r >> 1;
	if (p <= mid) return query(l, mid, lch, p);
	else return query(mid + 1, r, rch, p);
}

void update(int l, int r, int rt, int L, int R, long long delta) {
	if (L <= l && r <= R) {
		// ans[rt] += delta * (siz[rt] - siz[son[rt]]);
		del[rt] += delta;

		pushdown(l, r, rt);
		return;
	}
	pushdown(l, r, rt);
	int mid = l + r >> 1;
	if (L <= mid) update(l, mid, lch, L, R, delta);
	if (mid < R) update(mid + 1, r, rch, L, R, delta);
}

void pppr(int l, int r, int rt, int p, long long v) {
	if (l == r) {
		poop[l] += v;
		return;
	}
	pushdown(l, r, rt);
	int mid = l + r >> 1;
	if (p <= mid) pppr(lson, p, v);
	else pppr(rson, p, v);
}

void puewr(int l, int r, int rt, int L, int R, long long delta) {
	if (L <= l && r <= R) {
		del2[rt] += delta;
		pushdown(l, r, rt);
		return;
	}
	pushdown(l, r, rt);
	int mid = l + r >> 1;
	if (L <= mid) puewr(lson, L, R, delta);
	if (mid < R) puewr(rson, L, R, delta);
}

int main() {
	freopen("3683.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 2, x; i <= n; i++) {
		scanf("%d", &x);
		edges[x].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		scanf("%lld", &w[i]);
	dfspre(1);
	dfsmrk(1, 1);
	// build(1, n, 1);
	char op[3];
	int x;
	long long val;
	while (m--) {
		scanf("%s", op);
		if (op[0] == 'Q') {
			scanf("%d", &x);
			printf("%.10lf\n", 2. * query(1, n, 1, mrk[x]) / num[mrk[x]]);

		} else if (op[0] == 'S') {
			scanf("%d %lld", &x, &val);
			pppr(1, n, 1, mrk[x], val * (siz[x] - 1));

			while (fa[x]) {
				if (son[fa[x]] == x) {
					update(1, n, 1, mrk[top[x]], mrk[fa[x]], val);
					x = top[x];
				} else {
					pppr(1, n, 1, mrk[fa[x]], val * (siz[fa[x]] - siz[x]));
					x = fa[x];
				}
			}

		} else {
			scanf("%d %lld", &x, &val);
			puewr(1, n, 1, mrk[x], ed[x], val);
			val = val * siz[x];
			while (fa[x]) {
				if (son[fa[x]] == x) {
					update(1, n, 1, mrk[top[x]], mrk[fa[x]], val);
					x = top[x];
				} else {
					pppr(1, n, 1, mrk[fa[x]], val * (siz[fa[x]] - siz[x]));
					x = fa[x];
				}
			}
		}
	}



	return 0;
}
