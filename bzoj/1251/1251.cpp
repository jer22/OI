#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 50005;

int n, m;
int root, sz = 0;
int mx[MAXN], v[MAXN];
int siz[MAXN], tr[MAXN][2];
int fa[MAXN], id[MAXN];
int tag[MAXN], rev[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
	mx[rt] = max(max(mx[l], mx[r]), v[rt]);
}

void pushdown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	if (tag[rt]) {
		if (l) {
			v[l] += tag[rt];
			mx[l] += tag[rt];
			tag[l] += tag[rt];
		}
		if (r) {
			v[r] += tag[rt];
			mx[r] += tag[rt];
			tag[r] += tag[rt];
		}
		tag[rt] = 0;
	}
	if (rev[rt]) {
		rev[rt] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
		swap(tr[rt][0], tr[rt][1]);
	}
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = id[l], last = id[rt];
	if (l == r) {
		siz[now] = 1;
		fa[now] = last;
		if (l < rt) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = id[mid];
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	pushup(now);
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
}

void rotate(int x, int &k) {
	int y = fa[x], z = fa[y];
	int l, r;
	if (tr[y][0] == x) l = 0;
	else l = 1;
	r = l ^ 1;
	if (y == k) k = x;
	else {
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

void splay(int x, int &k) {
	while (x != k) {
		int y = fa[x], z = fa[y];
		if (y != k) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x, k);
			else rotate(y, k);
		}
		rotate(x, k);
	}
}

int find(int rt, int rank) {
	pushdown(rt);
	int l = tr[rt][0], r = tr[rt][1];
	if (siz[l] + 1 == rank) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
}

void add(int l, int r) {
	int value;
	scanf("%d", &value);
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	tag[z] += value;
	v[z] += value;
	mx[z] += value;
}

void reverse(int l, int r) {
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	rev[z] ^= 1;
}

void query(int l, int r) {
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	printf("%d\n", mx[z]);
}

int main() {
	freopen("1251.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n + 2; i++)
		id[i] = ++sz;
	mx[0] = -INF;
	build(1, n + 2, 0);
	root = n + 3 >> 1;
	int op, l, r;
	for (int i = 0; i < m; i++) {
		scanf("%d", &op);
		scanf("%d %d", &l, &r);
		if (op == 1) add(l, r);
		if (op == 2) reverse(l, r);
		if (op == 3) query(l, r);
	}

	return 0;
}
