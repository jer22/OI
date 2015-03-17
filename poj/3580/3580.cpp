#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 100005
#define INF 0x3f3f3f3f

using namespace std;

int n, q;
int root, sz;
int arr[MAXN], id[MAXN];
int fa[MAXN], tr[MAXN][2];
int siz[MAXN];
int rev[MAXN], add[MAXN];
int mi[MAXN], v[MAXN];
int rec[MAXN];

void pushUp(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	siz[rt] = siz[l] + siz[r] + 1;
	mi[rt] = min(min(mi[l], mi[r]), v[rt]);
}

void pushDown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	if (add[rt]) {
		v[rt] += add[rt];
		if (l) { add[l] += add[rt]; mi[l] += add[rt]; }
		if (r) { add[r] += add[rt]; mi[r] += add[rt]; }
		add[rt] = 0;
	}
	if (rev[rt]) {
		rev[rt] ^= 1;
		rev[l] ^= 1;
		rev[r] ^= 1;
		swap(tr[rt][0], tr[rt][1]);
	}
}

void build(int l, int r, int rt) {
	if (l > r) return;
	int now = id[l], last = id[rt];
	if (l == r) {
		v[now] = mi[now] = arr[l];
		fa[now] = last;
		siz[now] = 1;
		rev[now] = add[now] = 0;
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

int find(int rt, int rank) {
	pushDown(rt);
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

void addUp(int a, int b) {
	int c;
	scanf("%d", &c);
	int x = find(root, a);
	int y = find(root, b + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	add[z] += c;
	mi[z] += c;
	pushUp(y);
	pushUp(x);
}

void getMin(int a, int b) {
	int x = find(root, a);
	int y = find(root, b + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	printf("%d\n", mi[z]);
	pushUp(y);
	pushUp(x);
}

void reverse(int a, int b) {
	int x = find(root, a);
	int y = find(root, b + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	rev[z] ^= 1;
	pushUp(y);
	pushUp(x);
}

void revolve(int a, int b) {
	int k;
	scanf("%d", &k);
	int len = b - a + 1;
	k %= len;
	if (k < 0) k += len;
	if (k) {
		reverse(a, b - k);
		reverse(b - k + 1, b);
		reverse(a, b);
	}
}

void ins(int a, int b) {
	int k = a;
	arr[1] = b;
	if (rec[0]) id[1] = rec[rec[0]--];
	else id[1] = ++sz;
	build(1, 1, 0);
	int x = find(root, k + 1);
	int y = find(root, k + 2);
	int z = id[1];
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
	add[rt] = rev[rt] = 0;
	rec[++rec[0]] = rt;
}

void del() {
	int k;
	scanf("%d", &k);
	int x = find(root, k);
	int y = find(root, k + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	reclaim(z);
	tr[y][0] = 0;
	pushUp(y);
	pushUp(z);
}

int main() {
	freopen("3580.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i + 1]);
	for (int i = 1; i <= n + 2; i++)
		id[i] = ++sz;
	mi[0] = INF;
	arr[1] = arr[n + 2] = INF;
	build(1, n + 2, 0);
	root = n + 3 >> 1;
	scanf("%d", &q);
	char op[8];
	int a, b;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		if (op[0] == 'D') del();
		else {
			scanf("%d %d", &a, &b);
			if (op[0] == 'A') addUp(a, b);
			if (op[0] == 'M') getMin(a, b);
			if (op[0] == 'R')
				if (op[3] == 'E') reverse(a, b);
				else { revolve(a, b); }
			if (op[0] == 'I') ins(a, b);
		}
	}
	return 0;
}
