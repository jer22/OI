#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500005;

int n, q;
int val[MAXN], xo[MAXN];
bool rev[MAXN];
int tr[MAXN][2], fa[MAXN];
int st[MAXN], top = 0;

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	xo[x] = xo[l] ^ xo[r] ^ val[x];
}

void pushdown(int x) {
	if (rev[x]) {
		int l = tr[x][0], r = tr[x][1];
		rev[x] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
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
	st[++top] = x;
	for (int i = x; !isroot(i); i = fa[i])
		st[++top] = fa[i];
	while (top) pushdown(st[top--]);
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[z][0] == y ^ tr[y][0] == x) rotate(x);
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

int query(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	return xo[y];
}

void change(int x, int y) {
	access(x);
	splay(x);
	val[x] = y;
	pushup(x);
}

int main() {
	freopen("2819.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		xo[i] = val[i];
	}
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		link(a, b);
	}
	scanf("%d", &q);
	char op[3];
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		scanf("%d %d", &a, &b);
		if (op[0] == 'Q') {
			int t = query(a, b);
			if (t != 0) printf("Yes\n");
			else printf("No\n");
		} else {
			change(a, b);
		}
	}


	return 0;
}
