#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 200005;

int n, m;
int rev[MAXN], cover[MAXN];
int tr[MAXN][2], fa[MAXN];
int q[MAXN], top = 0;
int val[MAXN], loop[MAXN];

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
	while (!isroot(x)) {
		int y = fa[x], z = fa[y];
		if (!isroot(y)) {
			if (tr[y][0] == x ^ tr[z][0] == y) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
int access(int x) {
	int tt = x;
	for (int t = 0; x; t = x, x = fa[x]) {
		splay(x), tr[x][1] = t;
		tt = x;
	}
	return tt;
}
int find(int x) {
	access(x);
	splay(x);
	while (tr[x][0]) x = tr[x][0];
	return x;
}
void cut(int y) {
	splay(y);
	if (loop[y]) {
		loop[y] = 0;
		return;
	}
	int t = tr[y][0];
	if (t) while (tr[t][1]) t = tr[t][1];
	else t = fa[y];
	if (!t) return;
	access(t);
	splay(y);

	fa[y] = 0;
}
int parent[MAXN];
void conn(int x, int y) {
	parent[x] = y;

	if (!y) {
		loop[x] = 0;
		fa[x] = 0;
		return;
	}
	int a = find(x);
	int b = find(y);
	if (a == b) {
		loop[a] = y;
		parent[x] = 0;
	} else {
		loop[x] = 0;
		access(x);
		splay(x);
		fa[x] = y;
		access(b);
	}
}
int query(int x) {
	return val[x];
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &parent[i]);
		if (!parent[i]) continue;
		if (find(parent[i]) != find(i)) {
			fa[i] = parent[i];
		} else {
			loop[i] = parent[i];
			parent[i] = 0;
		}		
	}

	int op, a, b;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d %d", &a, &b);
			int t = find(a);
			if (loop[t]) {
				if (t == a) {
					conn(a, b);
				} else {
					cut(a);
					conn(t, loop[t]);
					conn(a, b);
				}
			} else {
				if (t == a) {
					conn(a, b);
				} else {
					cut(a);
					conn(a, b);
				}
			}
		} else {
			scanf("%d", &a);
			int rt = find(a);
			if (loop[rt]) printf("-1\n");
			else printf("%d\n", rt);
		}
	}
	return 0;
}
