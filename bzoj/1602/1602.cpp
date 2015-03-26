#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 2005;

int n, q;
bool rev[MAXN];
int st[MAXN], top = 0;
int siz[MAXN], fa[MAXN], tr[MAXN][2], v[MAXN], sum[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
	sum[rt] = sum[l] + sum[r] + v[rt];
}

void pushdown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	if (rev[rt]) {
		rev[rt] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
		swap(tr[rt][0], tr[rt][1]);
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

void cut(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	tr[y][0] = fa[tr[y][0]] = 0;
}

int main() {
	freopen("1602.in", "r", stdin);
	scanf("%d %d", &n, &q);
	int a, b, c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		v[i + n] = c;
		sum[i + n] = c;
		link(a, i + n);
		link(b, i + n);
	}
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		makeroot(a);
		access(b);
		splay(b);
		cout << sum[b] << endl;
	}

	return 0;
}
