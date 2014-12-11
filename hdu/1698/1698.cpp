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

int T;
int n, q;
int sum[MAXN];
int change[MAXN];

void pushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushDown(int rt, int len) {
	if (change[rt]) {
		change[rt << 1] = change[rt];
		change[rt << 1 | 1] = change[rt];
		sum[rt << 1] = change[rt] * (len - (len >> 1));
		sum[rt << 1 | 1] = change[rt] * (len >> 1);
		change[rt] = 0;
	}
}

void buildTree(int l, int r, int rt) {
	change[rt] = 0;
	sum[rt] = 0;
	if (l == r) {
		sum[rt] = 1;
		return;
	}
	buildTree(lch);
	buildTree(rch);
	pushUp(rt);
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && R >= r) {
		change[rt] = v;
		sum[rt] = v * (r - l + 1);
		return;
	}
	pushDown(rt, r - l + 1);
	if (L <= m) update(L, R, v, lch);
	if (R > m) update(L, R, v, rch);
	pushUp(rt);
}

int main() {
	freopen("1698.in", "r", stdin);
	scanf("%d", &T);
	int t = 0;
	while (T--) {
		t++;
		scanf("%d %d", &n, &q);
		buildTree(root);
		int a, b, c;
		for (int i = 1; i <= q; i++) {
			scanf("%d %d %d", &a, &b, &c);
			update(a, b, c, root);
		}
		printf("Case %d: The total value of the hook is %d.\n", t, sum[1]);
	}
	return 0;
}
