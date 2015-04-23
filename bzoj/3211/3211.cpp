#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define MAXN 100005

using namespace std;

int n, m;
long long sum[MAXN << 2];
bool fin[MAXN << 2];

void pushup(int rt) {
	sum[rt] = sum[lch] + sum[rch];
	fin[rt] = fin[lch] & fin[rch];
}

void pushdown(int l, int r, int rt) {
	if (fin[rt]) return;
	if (l == r) {
		sum[rt] = sqrt(sum[rt]);
		if (sum[rt] <= 1) fin[rt] = 1;
		return;
	}
	int mid = l + r >> 1;
	pushdown(lson);
	pushdown(rson);
	pushup(rt);
}

void build(int l, int r, int rt) {
	if (l == r) {
		scanf("%lld", &sum[rt]);
		if (sum[rt] <= 1) fin[rt] = 1;
		return;
	}
	int mid = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

long long query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R)
		return sum[rt];
	int mid = l + r >> 1;
	long long ans = 0;
	if (L <= mid) ans += query(lson, L, R);
	if (R > mid) ans += query(rson, L, R);
	return ans;
}

void change(int l, int r, int rt, int L, int R) {
	if (fin[rt]) return;
	if (L <= l && r <= R) {
		pushdown(l, r, rt);
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) change(lson, L, R);
	if (R > mid) change(rson, L, R);
	pushup(rt);
}

int main() {
	freopen("3211.in", "r", stdin);
	scanf("%d", &n);
	build(1, n, 1);
	int a, b, c;
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		if (a == 1) printf("%lld\n", query(1, n, 1, b, c));
		else change(1, n, 1, b, c);
	}

	return 0;
}
