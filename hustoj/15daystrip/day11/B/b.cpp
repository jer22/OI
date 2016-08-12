#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 5000005
#define INF 1000000000

using namespace std;

int T, n, q;
int sz, root;
int arr[MAXN], id[MAXN];
int v[MAXN];
int fa[MAXN], siz[MAXN], sum[MAXN], tr[MAXN][2];
bool rev[MAXN], tag[MAXN];
int rec[MAXN];
int lmax[MAXN], rmax[MAXN], mmax[MAXN];

void pushUp(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
	sum[rt] = sum[l] + sum[r] + v[rt];
	mmax[rt] = max(mmax[l], mmax[r]);
	mmax[rt] = max(mmax[rt], lmax[r] + v[rt] + rmax[l]);
	lmax[rt] = max(lmax[l], sum[l] + v[rt] + lmax[r]);
	rmax[rt] = max(rmax[r], sum[r] + v[rt] + rmax[l]);
}

void pushDown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	if (tag[rt]) {
		tag[rt] = rev[rt] = 0;
		if (l) {
			tag[l] = 1;
			v[l] = v[rt];
			sum[l] = v[rt] * siz[l];
		}
		if (r) {
			tag[r] = 1;
			v[r] = v[rt];
			sum[r] = v[rt] * siz[r];
		}
		if (v[rt] >= 0) {
			if (l) lmax[l] = rmax[l] = mmax[l] = sum[l];
			if (r) lmax[r] = rmax[r] = mmax[r] = sum[r];
		} else {
			if (l) lmax[l] = rmax[l] = 0, mmax[l] = v[rt];
			if (r) lmax[r] = rmax[r] = 0, mmax[r] = v[rt];
		}
	}
	if (rev[rt]) {
		rev[rt] = 0;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(lmax[l], rmax[l]);
		swap(lmax[r], rmax[r]);
		swap(tr[l][0], tr[l][1]);
		swap(tr[r][0], tr[r][1]);
		pushUp(rt);
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

int find(int rt, int rank) {
	if (tag[rt] || rev[rt]) pushDown(rt);
	int l = tr[rt][0], r = tr[rt][1];
	if (siz[l] + 1 == rank) return rt;
	if (siz[l] + 1 > rank) return find(l, rank);
	return find(r, rank - siz[l] - 1);
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = id[l], last = id[rt];
	if (l == r) {
		fa[now] = last;
		siz[now] = 1;
		sum[now] = v[now] = mmax[now] = arr[l];
		if (arr[l] >= 0) lmax[now] = rmax[now] = arr[l];
		else lmax[now] = rmax[now] = 0;
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
	pushUp(now);
	if (mid < rt) tr[last][0] = now;
	else tr[last][1] = now;
}

int getSum(int k, int len) {
	int x = find(root, k);
	int y = find(root, k + len + 1);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	return sum[z];
}

void cover(int k, int len, int c) {
	int x = find(root, k);
	int y = find(root, k + len + 1);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	v[z] = c;
	tag[z] = 1;
	sum[z] = v[z] * siz[z];
	if (c >= 0) lmax[z] = rmax[z] = mmax[z] = sum[z];
	else lmax[z] = rmax[z] = 0, mmax[z] = v[z];
	pushUp(y);
	pushUp(x);
}

void reverse(int k, int len) {
	int x = find(root, k);
	int y = find(root, k + len + 1);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	if (!tag[z]) {
		rev[z] ^= 1;
		swap(tr[z][0], tr[z][1]);
		swap(lmax[z], rmax[z]);
	}
	pushUp(y);
	pushUp(x);
}

void insert(int k, int len) {
	for (int i = 1; i <= len; i++) {
		scanf("%d", &arr[i]);
		if (rec[0]) id[i] = rec[rec[0]--];
		else id[i] = ++sz;
	}
	build(1, len, 0);
	int x = find(root, k + 1);
	int y = find(root, k + 2);
	int z = id[len + 1 >> 1];
	splay(x, root);
	splay(y, tr[root][1]);
	tr[y][0] = z;
	fa[z] = y;
	pushUp(y);
	pushUp(x);
}

void reclaim(int rt) {
	if (!rt) return;
	int l = tr[rt][0], r = tr[rt][1];
	reclaim(l);
	reclaim(r);
	fa[rt] = tr[rt][0] = tr[rt][1] = 0;
	tag[rt] = rev[rt] = 0;
	rec[++rec[0]] = rt;
}

void del(int k, int len) {
	int x = find(root, k);
	int y = find(root, k + len + 1);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	// reclaim(z);
	tr[y][0] = 0;
	pushUp(y);  
	pushUp(x);
}

int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		memset(tag, 0, sizeof(tag));
		memset(rev, 0, sizeof(rev));
		memset(tr, 0, sizeof(tr));
		for (int i = 1; i <= n; i++)
	  		scanf("%d", &arr[i + 1]);
	  	sz = 0;
	  	for (int i = 1; i <= n + 2; i++)
			id[i] = ++sz;
		arr[1] = arr[n + 2] = -INF;
		mmax[0] = -INF;
		build(1, n + 2, 0);
		root = n + 3 >> 1;
		char op[10];
		int x, y, z;
		for (int i = 0; i < q; i++) {
			scanf("%s", op);
			if (op[0] == 'R') {
				scanf("%d %d", &x, &y);
				reverse(x, y);
			} else if (op[0] == 'M') {
				if (op[2] == 'K') {
					scanf("%d %d %d", &x, &y, &z);
					cover(x, y, z);
				} else printf("%d\n", mmax[root]);
			} else if (op[0] == 'G') {
				scanf("%d %d", &x, &y);
				printf("%d\n", getSum(x, y));
			} else if (op[0] == 'I') {
				scanf("%d %d", &x, &y);
				insert(x, y);
			} else {
				scanf("%d %d", &x, &y);
				del(x, y);
			}
		}

	}
	
	

	
	char op[10];
	
	return 0;
}