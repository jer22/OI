#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 100005;

int n;
int arr[MAXN], root[MAXN];
int lst[MAXN], nex[MAXN];
int ls[MAXN * 40], rs[MAXN * 40], siz[MAXN * 40], tot = 0;

void insert(int x, int &y, int l, int r, int p, int v) {
	y = ++tot;
	siz[y] = siz[x] + v;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int mid = l + r >> 1;
	if (p <= mid) insert(ls[x], ls[y], l, mid, p, v);
	else insert(rs[x], rs[y], mid + 1, r, p, v);
}

int query(int rt, int l, int r, int k) {
	if (l == r) return l;
	int mid = l + r >> 1;
	if (siz[ls[rt]] >= k) return query(ls[rt], l, mid, k);
	return query(rs[rt], mid + 1, r, k - siz[ls[rt]]);
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		nex[i] = n + 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		if (!lst[arr[i]]) insert(root[0], root[0], 1, n + 1, i, 1);
		nex[lst[arr[i]]] = i;
		lst[arr[i]] = i;
	}
	for (int i = 1; i <= n; i++) {
		root[i] = root[i - 1];
		if (nex[i] != n + 1) insert(root[i], root[i], 1, n + 1, nex[i], 1);
		insert(root[i], root[i], 1, n + 1, i, -1);
	}
	for (int k = 1; k <= n; k++) {
		int l = 0;
		int ans = 0;
		while (l < n) {
			int r = query(root[l], 1, n + 1, k + 1);
			l = r - 1;
			ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}
