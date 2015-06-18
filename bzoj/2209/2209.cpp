#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, q;
int sz, root;
int arr[MAXN], v[MAXN];
int fa[MAXN], siz[MAXN], tr[MAXN][2];
bool rev[MAXN], tag[MAXN];
int sum[MAXN];
int lmax[MAXN], lmin[MAXN], rmax[MAXN], rmin[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	sum[rt] = sum[l] + sum[r] + v[rt];
	siz[rt] = siz[l] + siz[r] + 1;
	lmax[rt] = max(lmax[l], sum[l] + v[rt] + lmax[r]);
	rmax[rt] = max(rmax[r], sum[r] + v[rt] + rmax[l]);

	lmin[rt] = min(lmin[l], sum[l] + v[rt]);
	lmin[rt] = min(lmin[rt], sum[l] + v[rt] + lmin[r]);


	rmin[rt] = min(rmin[r], v[rt] + sum[r]);
	rmin[rt] = min(rmin[rt], rmin[l] + v[rt] + sum[r]);
}

void pushdown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = l, last = rt;
	if (l == r) {
		fa[now] = last;
		siz[now] = 1;
		v[now] = sum[now] = arr[l];
		if (arr[l] >= 0) {
			lmax[now] = rmax[now] = arr[l];
			lmin[now] = rmin[now] = 0;
		}
		else {
			lmax[now] = rmax[now] = 0;
			lmin[now] = rmin[now] = arr[l];
		}
		if (l < rt) tr[last][0] = now;
		else tr[last][1] = now;
		return;
	}
	int mid = l + r >> 1;
	now = mid;
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	fa[now] = last;
	v[now] = arr[mid];
	pushup(now);
	cout << lmax[now] << endl;
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
}

int find(int rt, int rank) {
	if (rev[rt] || tag[rt]) pushdown(rt);
	int l = tr[rt][0], r = tr[rt][1];
	if (siz[l] + 1 == rank) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
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

int query(int a, int b) {
	int x = find(root, a + 1);
	int y = find(root, b + 1);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	int ans = -lmin[z] + 1 >> 1;
	ans += rmax[z] + 1 >> 1;
	return ans;
}

int main() {
	freopen("2209.in", "r", stdin);
	scanf("%d %d", &n, &q);
	char str[MAXN];
	scanf("%s", str);
	for (int i = 1; i <= n; i++) {
		if (str[i - 1] == '(') arr[i + 1] = 1;
		else arr[i + 1] = -1;
	}
	sz = n + 2;
	build(1, n + 2, 0);
	cout << rmax[root];
	root = n + 3 >> 1;
	int op, a, b;
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d", &op, &a, &b);
		if (!op) {
			// int ans = query(a, b);
			// cout << ans << endl;
		}
	}

	return 0;
}
