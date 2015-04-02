#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 300005;

int n;
int q[MAXN];
int v[MAXN], fa[MAXN], tr[MAXN][2];
int add[MAXN];
bool rev[MAXN];
int st[MAXN], top = 0;

void pushdown(int x) {
	int l = tr[x][0], r = tr[x][1];
	if (add[x]) {
		if (l) {
			add[l] += add[x];
			v[l] += add[x];
		}
		if (r) {
			add[r] += add[x];
			v[r] += add[x];
		}
		add[x] = 0;
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
		splay(x), tr[x][1] = t;
}

void makeroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}

void split(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
}

void link(int x, int y) {
	makeroot(x);
	fa[x] = y;
}

void addup(int x, int y) {
	split(x, y);
	add[y]++;
	v[y]++;
}

int main() {
	freopen("3631.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &q[i]);
	int x, y;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &x, &y);
		link(x, y);
	}
	for (int i = 1; i < n; i++) {
		x = q[i], y = q[i + 1];
		addup(x, y);
		split(y, y);
		add[y]--;
		v[y]--;
	}
	for (int i = 1; i <= n; i++) {
		splay(i);
		printf("%d\n", v[i]);
	}
	return 0;
}
