#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>

#define INF 0x3f3f3f3f

using namespace std;

const int MAXN = 80005;

int n, m;
int root, sz = 0;
int pos[MAXN], arr[MAXN];
int v[MAXN], id[MAXN], siz[MAXN], tr[MAXN][2], fa[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = id[l], last = id[rt];
	if (l == r) {
		siz[now] = 1;
		fa[now] = last;
		v[now] = arr[l];
		if (l < rt) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = id[mid];
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	v[now] = arr[mid];
	pushup(now);
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
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
	fa[tr[x][r]] =  y;
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
	if (siz[l] + 1 == rank) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
}

void del(int rank) {
	int x = find(root, rank - 1);
	int y = find(root, rank + 1);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	tr[y][0] = 0;
	fa[z] = siz[z] = 0;
	pushup(y);
	pushup(x);
}

void move(int k,int val) {
	int x, y, z = pos[k], rank;
	splay(z, root); rank = siz[tr[z][0]] + 1;
	del(rank);
	if (val == INF) x = find(root,n), y = find(root, n + 1);
	else if (val == -INF) x = find(root, 1), y = find(root , 2);
	else x = find(root, rank + val - 1), y = find(root, rank + val);
	splay(x, root); splay(y, tr[x][1]);
	siz[z] = 1; fa[z] = y; tr[y][0] = z;
	pushup(y); pushup(x);
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i + 1]);
		pos[arr[i + 1]] = i + 1;
	}
	for (int i = 1; i <= n + 2; i++)
		id[i] = ++sz;
	build(1, n + 2, 0);
	root = n + 3 >> 1;
	char op[10];
	int S, T;
	for (int i = 0; i < m; i++) {
		scanf("%s", op);
		scanf("%d", &S);
		if (op[0] == 'A') { splay(pos[S], root); printf("%d\n", siz[tr[pos[S]][0]] - 1); }
		if (op[0] == 'T') move(S, -INF);
		if (op[0] == 'B') move(S, INF);
		if (op[0] == 'I') { scanf("%d", &T); move(S, T); }
		if (op[0] == 'Q') printf("%d\n", v[find(root, S + 1)]);
	}

	return 0;
}
