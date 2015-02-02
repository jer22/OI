#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define MOD 9875321
#define MAXN 150005

using namespace std;

int siz, root;
int fa[MAXN];
int tr[MAXN][2];
int size[MAXN], v[MAXN], h[MAXN], p[MAXN];
char str[MAXN];
int n, m;

void update(int k) {
	int l = tr[k][0], r = tr[k][1];
	size[k] = size[l] + size[r] + 1;
	h[k] = h[l] + (long long)v[k] * p[size[l]] % MOD + (long long)p[size[l] + 1] * h[r] % MOD;
	h[k] %= MOD;
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
	update(y);
	update(x);
}

void splay(int x, int &k) {
	while (x != k) {
		int y = fa[x], z = fa[y];
		if (y != k) {
			if ((tr[y][0] == x) ^ (tr[z][0] == y)) rotate(x, k);
			else rotate(y, k);
		}
		rotate(x, k);
	}
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = l, last = rt;
	if (l == r) {
		v[now] = h[now] = str[now] - 'a' + 1;
		fa[now] = last;
		size[now] = 1;
		if (l < rt) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = mid;
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	v[now] = str[now] - 'a' + 1;
	fa[now] = last;
	update(now);
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
}

int find(int k, int rk) {
	int l = tr[k][0], r = tr[k][1];
	if (size[l] + 1 == rk) return k;
	else if (size[l] + 1 >= rk) return find(l, rk);
	else return find(r, rk - size[l] - 1);
}

void insert(int k, int val) {
	int x = find(root, k + 1);
	int y = find(root, k + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = ++siz;
	tr[y][0] = z;
	fa[z] = y;
	v[z] = val;
	update(z);
	update(y);
	update(x);
}

int query(int k, int val) {
	int x = find(root, k);
	int y = find(root, k + val + 1);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	return h[z];
}

int solve(int x, int y) {
	int l = 1, r = min(siz - x, siz - y) - 1;
	int ans = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (query(x, mid) == query(y, mid)) {
			ans = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	return ans;
}

int main() {
	freopen("1014.in", "r", stdin);
	scanf("%s", str + 2);
	n = strlen(str + 2);
	p[0] = 1;
	for (int i = 1; i < MAXN; i++) p[i] = p[i - 1] * 27 % MOD;
	build(1, n + 2, 0);
	siz = n + 2;
	root = n + 3 >> 1;
	scanf("%d", &m);
	char op[5];
	int x, y;
	for (int i = 1; i <= m; i++) {
		scanf("%s %d", op, &x);
		if (op[0] == 'Q') {
			scanf("%d", &y);
			printf("%d\n", solve(x, y));
		} else if (op[0] == 'R') {
			scanf("%s", op);
			x = find(root, x + 1);
			splay(x, root);
			v[root] = op[0] - 'a' + 1;
			update(root);
		} else if (op[0] == 'I') {
			scanf("%s", op);
			insert(x, op[0] - 'a' + 1);
		}
	}
	return 0;
}
