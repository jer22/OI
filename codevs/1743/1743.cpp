#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 300005;

int n, sz, root;
int arr[MAXN], size[MAXN], tr[MAXN][2], fa[MAXN];
int rev[MAXN];

void pushup(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	size[rt] = size[l] + size[r] + 1;
}

void pushdown(int rt) {
	int l = tr[rt][0], r = tr[rt][1];
	rev[rt] ^= 1;
	rev[l] ^= 1;
	rev[r] ^= 1;
	swap(tr[rt][0], tr[rt][1]);
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

void build(int l, int r, int f) {
	if (l > r) return;
	int mid = l + r >> 1;
	if (mid < f) tr[f][0] = mid;
	else tr[f][1] = mid;
	size[mid] = 1;
	fa[mid] = f;
	if (l == r) return;
	build(l, mid - 1, mid);
	build(mid + 1, r, mid);
	pushup(mid);
}

int find(int k, int rk) {
	if (rev[k]) pushdown(k);
	int l = tr[k][0], r = tr[k][1];
	if (size[l] + 1 == rk) return k;
	else if (size[l] >= rk) return find(l, rk);
	else return find(r, rk - size[l] - 1);
}

void rever(int l, int r) {
	int x = find(root, l);
	int y = find(root, r + 2);
	splay(x, root);
	splay(y, tr[x][1]);
	int z = tr[y][0];
	rev[z] ^= 1;
}

int main() {
	freopen("1743.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i + 1]);
	build(1, n + 2, 0);
	root = (n + 3) >> 1;
	int ans = 0;
	while (arr[find(root, 2)] != 1) {
		ans++;
		rever(1, arr[find(root, 2)]);
		if(ans > 100000) {
			cout << -1 << endl;
			return 0;
		}
	}
	cout << ans << endl;

	return 0;
}
