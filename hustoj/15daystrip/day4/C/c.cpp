#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 2048588;

int q;
int n = 0, sz = 0, root;
int cur = 0;
int t[MAXN], id[MAXN], tr[MAXN][2], size[MAXN], fa[MAXN];
int rec[MAXN], v[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	size[rt] = size[l] + size[r] + 1;
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

int find(int k, int rk) {
	int l = tr[k][0], r = tr[k][1];
	if (size[l] + 1 == rk) return k;
	else if (size[l] >= rk) return find(l, rk);
	else return find(r, rk - size[l] - 1);
}


void build(int l, int r, int f) {
	if (l > r) return;
	int now = id[l], last = id[f];
	if (l == r) {
		fa[now] = last;
		size[now] = 1;
		v[now] = t[l];
		if (l < f) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = id[mid];
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	v[now] = t[mid];
	pushup(now);
	if (mid < f) tr[last][0] = now;
	else tr[last][1] = now;
}

void del(int k, int len) {
	int x = find(root, k + 1);
	int y = find(root, k + len + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	tr[y][0] = 0;
	pushup(y);
	pushup(x);
}

void insert(int k, int len) {
	for (int i = 1; i <= len; i++)
		t[i] = getchar(), i -= (t[i] == 10);
	for (int i = 1; i <= len; i++)
		id[i] = ++sz;
	build(1, len, 0);
	int x = find(root, k + 1);
	int y = find(root, k + 2);
	int z = id[len + 1 >> 1];
	splay(x, root);
	splay(y, tr[root][1]);
	tr[y][0] = z;
	fa[z] = y;
	pushup(y);
	pushup(x);
}

void printout(int k) {
	if (!k) return;
	printout(tr[k][0]);
	printf("%c", v[k]);
	printout(tr[k][1]);
}

void query(int k, int len) {
	int x = find(root, k + 1);
	int y = find(root, k + len + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	printout(z);
	printf("\n");
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &q);
	for (int i = 1; i <= n + 2; i++)
		id[i] = ++sz;
	build(1, n + 2, 0);
	root = n + 3 >> 1;

	char s[20];
	int len = 0;
	while (q--) {
		scanf("%s", s);

		if (s[0] == 'M')
			scanf("%d", &cur);
		if (s[0] == 'P')
			cur--;
		if (s[0] == 'N')
			cur++;
		if (s[0] == 'I') {
			scanf("%d", &len);
			insert(cur, len);

		}
		if (s[0] == 'D') {
			scanf("%d", &len);
			del(cur, len);
		}

		if (s[0] == 'G') {
			scanf("%d", &len);
			query(cur, len);
		}
	}

	return 0;
}
