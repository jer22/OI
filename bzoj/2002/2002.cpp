#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
 
#define INF 0x3f3f3f3f
 
using namespace std;
 
const int MAXN = 200005;
 
int n, m;
int nex[MAXN], siz[MAXN], fa[MAXN], tr[MAXN][2];
bool rev[MAXN];
int q[MAXN], top = 0;
void pushup(int x) { siz[x] = siz[tr[x][0]] + siz[tr[x][1]] + 1; }
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
	q[++top] = x;
	for (int i = x; !isroot(i); i = fa[i])
		q[++top] = fa[i];
	for (int i = top; i; i--) pushdown(q[i]);
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
	int t = 0;
	while (x) {
		splay(x);
		tr[x][1] = t;
		t = x;
		x = fa[x];
	}
}
void makeroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}
void link(int x, int y) {
	makeroot(x);
	fa[x] = y;
	splay(x);
}
void cut(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
	tr[y][0] = fa[tr[y][0]] = 0;
}
 
int main() {
	freopen("2002.in", "r", stdin);
	scanf("%d", &n);
	int op, x, y;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &x);
		fa[i] = x + i;
		siz[i] = 1;
		if (fa[i] > n + 1) fa[i] = n + 1;
		nex[i] = fa[i];
	}
	siz[n + 1] = 1;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d", &x);
			x++;
			makeroot(n + 1);
			access(x);
			splay(x);
			printf("%d\n", siz[tr[x][0]]);
		} else {
			scanf("%d %d", &x, &y);
			x++;
			int t = min(x + y, n + 1);
			cut(x, nex[x]);
			link(x, t);
			nex[x] = t;
		}
	}
 
	return 0;
}