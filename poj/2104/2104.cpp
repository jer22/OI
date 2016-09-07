#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100005;

int n, q, tot;
int arr[MAXN], t[MAXN], cnt = 0;
int root[MAXN], ls[MAXN * 80], rs[MAXN * 80], siz[MAXN * 80];

void inithash() {
	for (int i = 1; i <= n; i++)
		t[i] = arr[i];
	sort(t + 1, t + n + 1);
	tot = unique(t + 1, t + n + 1) - t - 1;
}

int get(int x) {
	return lower_bound(t + 1, t + 1 + tot, x) - t;
}

void insert(int l, int r, int x, int &y, int v) {
	y = ++cnt;
	siz[y] = siz[x] + 1;
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int m = l + r >> 1;
	if (v <= m) insert(l, m, ls[x], ls[y], v);
	else insert(m + 1, r, rs[x], rs[y], v);
}

int query(int l, int r, int x, int y, int k) {
	if (l == r) return l;
	int m = l + r >> 1;
	if (siz[ls[y]] - siz[ls[x]] >= k) return query(l, m, ls[x], ls[y], k);
	else return query(m + 1, r, rs[x], rs[y], k - siz[ls[y]] + siz[ls[x]]);
}

int main() {
	freopen("2104.in", "r", stdin);
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	inithash();
	for (int i = 1; i <= n; i++)
		insert(1, tot, root[i - 1], root[i], get(arr[i]));
	int a, b, c;
	while (q--) {
		scanf("%d %d %d", &a, &b, &c);
		printf("%d\n", t[query(1, tot, root[a - 1], root[b], c)]);
	}

	return 0;
}
