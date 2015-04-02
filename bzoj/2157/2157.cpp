#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 40005;

int n, m;
int v[MAXN], fa[MAXN], tr[MAXN][2];
int sum[MAXN], mi[MAXN], mx[MAXN];
bool rev[MAXN];
int nag[MAXN];
int st[MAXN], top = 0;

void rever(int x) {
	v[x] = -v[x];
	sum[x] = -sum[x];
	swap(mi[x], mx[x]);
	mi[x] = -mi[x];
	mx[x] = -mx[x];
	nag[x] ^= 1;
}

void pushup(int x) {
	int l = tr[x][0], r = tr[x][1];
	sum[x] = sum[l] + sum[r] + v[x];
	mx[x] = max(mx[l], mx[r]);
	mi[x] = min(mi[l], mi[r]);
	if (x > n) mx[x] = max(mx[x], v[x]);
	if (x > n) mi[x] = min(mi[x], v[x]);
}

void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (nag[x]) {
		nag[x] = 0;
		if (l) rever(l);
		if (r) rever(r);
	}
	if (rev[x]) {
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

void split(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
}

void change(int x, int val) {
	splay(x);
	v[x] = val;
	pushup(x);
}

void getsum(int x, int y) {
	split(x, y);
	printf("%d\n", sum[y]);
}

void getmax(int x, int y) {
	split(x, y);
	printf("%d\n", mx[y]);
}

void getmin(int x, int y) {
	split(x, y);
	printf("%d\n", mi[y]);
}

void reverse(int x, int y) {
	split(x, y);
	rever(y);
}

int id[MAXN];
int main() {
	freopen("2157.in", "r", stdin);
	scanf("%d", &n);
	int x, y, w;
	for (int i = 0; i <= n; i++)
		mi[i] = 0x3f3f3f3f, mx[i] = -0x3f3f3f3f;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &x, &y, &w);
		x++;
		y++;
		id[i] = i + n;
		v[i + n] = sum[i + n] = mi[i + n] = mx[i + n] = w;
		link(x, i + n);
		link(y, i + n);
	}
	scanf("%d", &m);
	char op[5];
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == 'C') change(id[x], y);
		if (op[0] == 'M')
			if (op[1] == 'A') getmax(x + 1, y + 1);
			else getmin(x + 1, y + 1);
		if (op[0] == 'S') getsum(x + 1, y + 1);
		if (op[0] == 'N') reverse(x + 1, y + 1);
	}
	return 0;
}
