#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 300005

using namespace std;

int n, q;
int root, sz;
int id[MAXN];
int rev[MAXN];
int siz[MAXN];
int tr[MAXN][2];
int fa[MAXN];

void pushUp(int rt) {
	siz[rt] = siz[tr[rt][0]] + siz[tr[rt][1]] + 1;
}

void pushDown(int rt) {
	if (rev[rt]) {
		int l = tr[rt][0], r = tr[rt][1];
		rev[rt] = 0;
		rev[l] ^= 1; 
		rev[r] ^= 1;
		swap(tr[rt][0], tr[rt][1]);
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
	pushUp(y);
	pushUp(x);
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

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = id[l], last = id[rt];
	if (l == r) {
		fa[now] = last;
		siz[now] = 1;
		if (l < rt) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = id[mid];
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	pushUp(mid);
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
}

int find(int rt, int rank) {
	pushDown(rt);
	int l = tr[rt][0], r = tr[rt][1];
	if (siz[l] + 1 == rank) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
}

int find_min(int rt) {
	pushDown(rt);
	while (tr[rt][0]) {
		rt = tr[rt][0];
		pushDown(rt);
	}
	return rt;
}

void rever(int l, int r) {
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	rev[z] ^= 1;
}

void cut(int l, int r, int c) {
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int temp = tr[y][0];
	tr[y][0] = 0;
	pushUp(tr[root][1]);
	pushUp(root);
	int z = find(root, c + 1);
	splay(z, root);
	int m = find_min(tr[root][1]);
	splay(m, tr[root][1]);
	tr[tr[root][1]][0] = temp;
	fa[tr[tr[root][1]][0]] = tr[root][1];
	pushUp(tr[root][1]);
	pushUp(root);
}

int main() {
	freopen("3487.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		if (n == -1 && q == -1) break;
		sz = 0;
		for (int i = 1; i <= n + 2; i++) {
			id[i] = ++sz;
			rev[i] = fa[i] = siz[i] = tr[i][0] = tr[i][1] = 0;
		}
		build(1, n + 2, 0);
		root = n + 3 >> 1;
		char op[8];
		int x, y, z;
		for (int i = 0; i < q; i++) {
			scanf("%s", op);
			if (op[0] == 'C') {
				cin >> x >> y >> z;
				cut(x, y, z);
			} else {
				cin >> x >> y;
				rever(x, y);
			}
		}
		for (int i = 2; i <= n + 1; i++)
			cout << find(root, i) - 1 << " \n"[i == n + 1];
	}


	return 0;
}
