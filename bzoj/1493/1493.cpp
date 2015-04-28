#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 500005;

int n, c, m, sz, root;
int tr[MAXN][2], fa[MAXN];
int col[MAXN], sum[MAXN], lcc[MAXN], rcc[MAXN], siz[MAXN];
bool rev[MAXN], tag[MAXN];

void pushup(int x) {
	if (!x) return;
	int l = tr[x][0], r = tr[x][1];
	siz[x] = siz[l] + siz[r] + 1;
	sum[x] = sum[l] + sum[r] + 1;
	if (l && col[x] == rcc[l]) sum[x]--;
	if (r && col[x] == lcc[r]) sum[x]--;
	lcc[x] = rcc[x] = col[x];
	if (l) lcc[x] = lcc[l];
	if (r) rcc[x] = rcc[r];
}

void pushdown(int x) {
	if (!x) return;
	int l = tr[x][0], r = tr[x][1];
	if (tag[x]) {
		tag[x] = 0;
		if (l) sum[l] = tag[l] = 1, lcc[l] = rcc[l] = col[l] = col[x];
		if (r) sum[r] = tag[r] = 1, lcc[r] = rcc[r] = col[r] = col[x];
	}
	if (rev[x]) {
		rev[x] ^= 1, rev[l] ^= 1, rev[r] ^= 1;
		if (l) swap(lcc[l], rcc[l]), swap(tr[l][0], tr[l][1]);
		if (r) swap(lcc[r], rcc[r]), swap(tr[r][0], tr[r][1]);;
	}
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
	pushup(y), pushup(x);
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
	if (rev[rt] || tag[rt]) pushdown(rt);
	int l = tr[rt][0], r = tr[rt][1];
	if (rank == siz[l] + 1) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
}

void build(int l, int r, int f) {
	if (l > r) return;
	if (l == r) {
		lcc[l] = rcc[l] = col[l];
		fa[l] = f;
		sum[l] = siz[l] = 1;
		if (l < f) tr[f][0] = l;
		else tr[f][1] = l;
	}
	int mid = l + r >> 1;
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[mid] = f;
	pushup(mid);
	if (mid < f) tr[f][0] = mid;
	else tr[f][1] = mid;
}

void roll(int k) {
	if (!k || k == n) return;
	int x = find(root, n - k + 1);
	int y = find(root, n + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	x = y, y = tr[y][0];
	tr[x][0] = fa[y] = 0;
	pushup(x), pushup(fa[x]);
	int xx = find(root, 1);
	int yy = find(root, 2);
	splay(xx, root);
	splay(yy, tr[root][1]);
	tr[yy][0] = y;
	fa[y] = yy;
	pushup(yy), pushup(xx);
}

void flip() {
	if (n <= 2) return;
	int x = find(root, 2);
	int y = find(root, n + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	if (!tag[z]) {
		rev[z] ^= 1;
		swap(tr[z][0], tr[z][1]);
		swap(lcc[z], rcc[z]);
	}
	pushup(y), pushup(x);
}

void change(int a, int b, int v) {
	if (a <= b) {
		int x = find(root, a);
		int y = find(root, b + 2);
		splay(x, root);
		splay(y, tr[root][1]);
		int z = tr[y][0];
		tag[z] = sum[z] = 1;
		rcc[z] = lcc[z] = col[z] = v;;
		pushup(y), pushup(x);
	} else {
		roll(n - a + 1);
		change(1, b - a + n + 1, v);
		roll(a - 1);
	}
}

void swp(int a, int b) {	
	if (a == b) return;
	int x = col[find(root, a + 1)];
	int y = col[find(root, b + 1)];
	change(a, a, y);
	change(b, b, x);
}

int query() {
	if (!n) return 0;
	int ans = sum[root] - 2;
	int x = col[find(root, 2)];
	int y = col[find(root, n + 1)];
	if (x == y) ans = max(ans - 1, 1);
	return ans;
}

int countseg(int a, int b) {
	if (a <= b) {
		int x = find(root, a);
		int y = find(root, b + 2);
		splay(x, root);
		splay(y, tr[root][1]);
		return sum[tr[y][0]];
	} else {
		roll(n - a + 1);
		int ans = countseg(1, b - a + n + 1);
		roll(a - 1);
		return ans;
	}
}

int main() {
	freopen("1493.in", "r", stdin);
	scanf("%d %d", &n, &c);
	for (int i = 1; i <= n; i++)
		scanf("%d", &col[i + 1]);
	sz = n + 2;
	root = n + 3 >> 1;
	col[1] = col[n + 2] = 0;
	build(1, n + 2, 0);
	scanf("%d", &m);
	char op[5];
	int a, b, c;
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		if (op[0] == 'R') {
			scanf("%d", &a);
			roll(a);
		} else if (op[0] == 'F') flip();
		else if (op[0] == 'S') {
			scanf("%d %d", &a, &b);
			swp(a, b);
		}
		else if (op[0] == 'P') {
			scanf("%d %d %d", &a, &b, &c);
			change(a, b, c);
		} else {
			if (strlen(op) == 1) {
				int ans = query();
				printf("%d\n", ans);
			}
			else {
				scanf("%d %d", &a, &b);
				int ans = countseg(a, b);
				printf("%d\n", ans);
			}
		}
	}
	return 0;
}
