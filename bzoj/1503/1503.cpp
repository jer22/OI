#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 100005;

int q, m, d;
int root, sz;
int v[MAXN];
int siz[MAXN], fa[MAXN], tr[MAXN][2];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
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
	int l = tr[rt][0], r = tr[rt][1];
	if (siz[r] >= rank) return find(r, rank);
	if (siz[r] + 1 == rank) return v[rt];
	return find(l, rank - siz[r] - 1);
}

void ins(int num) {
	if (!root) {
		root = ++sz;
		v[sz] = num;
		siz[sz] = 1;
		return;
	}
	int p = root, z;
	while (p) {
		z = p;
		siz[p]++;
		if (num < v[p]) p = tr[p][0];
		else p = tr[p][1];
	}
	if (v[z] > num) tr[z][0] = ++sz;
	else tr[z][1] = ++sz;
	v[sz] = num;
	fa[sz] = z;
	siz[sz] = 1;
	splay(sz, root);
}

int del(int &x, int f) {
	if (!x) return 0;
	int k;
	if (v[x] + d < m) {
		k = del(tr[x][1], x) + siz[tr[x][0]] + 1;
		siz[tr[x][1]] = siz[x] - k;
		x = tr[x][1];
		fa[x] = f;
	} else {
		k = del(tr[x][0], x);
		siz[x] -= k;
	}
	return k;
}

int main() {
	freopen("1503.in", "r", stdin);
	scanf("%d %d", &q, &m);
	char op[5];
	int ans = 0, k;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		scanf("%d", &k);
		if (op[0] == 'I')
			if (k >= m) ins(k - d);
		if (op[0] == 'A') d += k;
		if (op[0] == 'S') {
			d -= k;
			ans += del(root, 0);
		}
		if (op[0] == 'F') {
			if (k <= siz[root]) printf("%d\n", find(root, k) + d);
			else printf("-1\n"); 
		}
	}
	printf("%d\n", ans);
	return 0;
}
