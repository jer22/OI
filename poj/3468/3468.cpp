#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define root 1, n, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
#define m ((l + r) >> 1)

using namespace std;

const int MAXN = 100000 << 2;

int n, q;
long long sum[MAXN];
long long add[MAXN];

void pushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushDown(int rt, int len) {
	if (add[rt]) {
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		sum[rt << 1] += add[rt] * (len - (len >> 1));
		sum[rt << 1 | 1] += add[rt] * (len >> 1);
		add[rt] = 0;
	}
}

void buildTree(int l, int r, int rt) {
	sum[rt] = add[rt] = 0;
	if (l == r) {
		scanf("%lld", &sum[rt]);
		return;
	}
	buildTree(lch);
	buildTree(rch);
	pushUp(rt);
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && R >= r) {
		add[rt] += v;
		sum[rt] += (long long)v * (r - l + 1);
		return;
	}
	pushDown(rt, r - l + 1);
	if (L <= m) update(L, R, v, lch);
	if (R > m) update(L, R, v, rch);
	pushUp(rt);
}

long long query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	pushDown(rt, r - l + 1);
	long long ans = 0;
	if (L <= m) ans += query(L, R, lch);
	if (R > m) ans += query(L, R, rch);
	return ans;
}

int main() {
	freopen("3468.in", "r", stdin);
	scanf("%d %d", &n, &q);
	buildTree(root);
	char ch[3];
	for (int i = 1; i <= q; i++) {
		scanf("%s", ch);
		int a, b, c;
		if (ch[0] == 'C') {
			scanf("%d %d %d", &a, &b, &c);
			update(a, b, c, root);
		} else {
			scanf("%d %d", &a, &b);
			printf("%lld\n", query(a, b, root));
		}
	}

	return 0;
}
