#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400005;

int n, m, q, ty;
int rev[MAXN];
int tr[MAXN][2], fa[MAXN];
int qq[MAXN], top = 0;
int val[MAXN], mi[MAXN];
pair<int, int> es[MAXN >> 1];

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	mi[x] = min(min(mi[l], mi[r]), val[x]);
}
void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (rev[x]) {
		rev[x] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(tr[x][0], tr[x][1]);
	}
}
bool isroot(int x) {
	return tr[fa[x]][0] != x && tr[fa[x]][1] != x;
}
void rotate(int x) {
	int y = fa[x], z = fa[y];
	int l, r;
	if (tr[y][0] == x) l = 0;
	else l = 1;
	r = l ^ 1;
	if (!isroot(y)) {
		if (tr[z][0] == y) tr[z][0] = x;
		else tr[z][1] = x;
	}
	fa[x] = z;
	fa[y] = x;
	fa[tr[x][r]] = y;
	tr[y][l] = tr[x][r];
	tr[x][r] = y;
	pushup(y);
	pushup(x);
}
void splay(int x) {
	top = 0;
	qq[++top] = x;
	for (int i = x; !isroot(i); i = fa[i])
		qq[++top] = fa[i];
	while (top) pushdown(qq[top--]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x) {
	for (int t = 0; x; t = x, x = fa[x])
		splay(x), tr[x][1] = t, pushup(x);
}
void makeroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}
void link(int x, int y) {
	makeroot(x);
	fa[x] = y;
}
void cut(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	tr[y][0] = fa[tr[y][0]] = 0;
	pushup(y);
}
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}
int query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	return mi[y];
}

int ntr[MAXN >> 1];
int root[MAXN >> 1], ls[MAXN * 20], rs[MAXN * 20], siz[MAXN * 20], cnt = 0;
void insert(int x, int &y, int l, int r, int v) {
	y = ++cnt;
	siz[y] = siz[x] + 1;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int m = l + r >> 1;
	if (v <= m) insert(ls[x], ls[y], l, m, v);
	else insert(rs[x], rs[y], m + 1, r, v);
}

int query(int x, int y, int l, int r, int k) {
	if (l == r) return siz[y] - siz[x];
	int mid = l + r >> 1;
	if (k <= mid) return query(ls[x], ls[y], l, mid, k);
	else return siz[ls[y]] - siz[ls[x]] + query(rs[x], rs[y], mid + 1, r, k);
}
int main() {
	freopen("3514.in", "r", stdin);
	scanf("%d %d %d %d", &n, &m, &q, &ty);
	int a, b;
	memset(val, 0x3f, sizeof(val));
	memset(mi, 0x3f, sizeof(mi));
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		val[i + n] = i;
		es[i] = make_pair(a, b);
		if (a == b) {
			ntr[i] = i;
			continue;
		}
		if (find(a) == find(b)) {
			int id = query(a, b);
			ntr[i] = id;
			cut(id + n, es[id].first);
			cut(id + n, es[id].second);
		} else ntr[i] = 0;
		link(a, i + n);
		link(b, i + n);
	}
	for (int i = 1; i <= m; i++)
		insert(root[i - 1], root[i], 0, m, ntr[i]);
	int lst = 0;
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		a ^= lst, b ^= lst;
		int ans = n - query(root[a - 1], root[b], 0, m, a - 1);
		if (ty) lst = ans;
		printf("%d\n", ans);
	}


	return 0;
}
