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
		mi[rt] += add[rt];
		add[l] += add[rt];
		add[r] += add[rt];
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

void addUp() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	int x = find(root, a);
	int y = find(root, b + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	add[z] += c;
	pushUp(y);
	pushUp(x);
}

void getMin() {
	int a, b;
	scanf("%d %d", &a, &b);
	int x = find(root, a);
	int y = find(root, b + 2);
	splay(x, root);
	splay(y, tr[root][1]);
	int z = tr[y][0];
	printf("%d\n", mi[z]);
	pushUp(y);
	pushUp(x);
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
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		if (op[0] == 'A') addUp();
		if (op[0] == 'M') getMin();
	}

	return 0;
}
