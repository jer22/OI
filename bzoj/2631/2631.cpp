#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 100005;
const int MOD = 51061;

int n, q;
int st[MAXN], top = 0;
unsigned int fa[MAXN], tr[MAXN][2], siz[MAXN], sum[MAXN], v[MAXN];
unsigned int add[MAXN], mul[MAXN];
bool rev[MAXN];
void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
	siz[rt] %= MOD;
	sum[rt] = sum[l] + sum[r] + v[rt];
	sum[rt] %= MOD;
}

void lazy(int rt, int m, int a) {
	v[rt] = (v[rt] * m + a) % MOD; 
	sum[rt] = (sum[rt] * m + a * siz[rt]) % MOD;
	add[rt] = (add[rt] * m + a) % MOD;
	mul[rt] = (mul[rt] * m) % MOD;
}

void pushdown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	if (rev[rt]) {
		rev[rt] ^= 1; rev[l] ^= 1; rev[r] ^= 1;
		swap(tr[rt][0], tr[rt][1]);
	}
	if (mul[rt] != 1 || add[rt]) {
		if (l) lazy(l, mul[rt], add[rt]);
		if (r) lazy(r, mul[rt], add[rt]);
		mul[rt] = 1;
		add[rt] = 0;
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
			rotate(y);
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

void addup(int x, int y) {
	int c;
	scanf("%d",&c);
	makeroot(x);
	access(y);
	splay(y);
	lazy(y, 1, c);
}

void linkcut(int x, int y) {
	cut(x, y);
	scanf(" %d %d", &x, &y);
	link(x, y);
}

void multi(int x, int y) {
	int c;
	scanf("%d", &c);
	makeroot(x);
	access(y);
	splay(y);
	lazy(y, c, 0);
}

void calc(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	printf("%d\n", sum[y]);
}

int main() {
	freopen("2631.in", "r", stdin);
	scanf("%d %d", &n, &q);
	int x, y;
	for (int i = 1; i <= n; i++)
		mul[i] = v[i] = 1;
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &x, &y);
		link(x, y);
	}
	char op[5];
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		scanf("%d %d", &x, &y);
		if (op[0] == '+') addup(x, y);
		if (op[0] == '-') linkcut(x, y);
		if (op[0] == '*') multi(x, y);
		if (op[0] == '/') calc(x, y);
	}

	return 0;
}
