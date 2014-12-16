#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, lef
#define rch m + 1, r, rig
#define lef rt << 1
#define rig rt << 1 | 1
#define roo 1, n, 1
#define this l, r, rt

using namespace std;

const int MAXN = 100002;

int T;
int n, q;
int lsum[MAXN << 2], rsum[MAXN << 2], msum[MAXN << 2], flag[MAXN << 2];
int add[MAXN << 2];
int lx[MAXN << 2], rx[MAXN << 2];
void pushUp(int l, int r, int rt) {
	int m = (l + r) >> 1;
	lsum[rt] = lsum[lef];
	rsum[rt] = rsum[rig];
	msum[rt] = max(msum[lef], msum[rig]);
	if (rx[lef] < lx[rig]) {
		msum[rt] = max(msum[rt], rsum[lef] + lsum[rig]);
		if (flag[lef]) lsum[rt] += lsum[rig];
		if (flag[rig]) rsum[rt] += rsum[lef];
	}
	lx[rt] = lx[lef];
	rx[rt] = rx[rig];
	if (msum[rt] == r - l + 1) flag[rt] = 1;
	else flag[rt] = 0;
}

void pushDown(int rt) {
	if (add[rt]) {
		add[lef] += add[rt];
		add[rig] += add[rt];
		lx[lef] += add[rt];
		rx[lef] += add[rt];
		lx[rig] += add[rt];
		rx[rig] += add[rt];
		add[rt] = 0;
	}
}

void buildTree(int l, int r, int rt) {
	add[rt] = 0;
	lsum[rt] = rsum[rt] = msum[rt] = flag[rt] = 1;
	if (l == r) {
		scanf("%d", &lx[rt]);
		rx[rt] = lx[rt];
		return;
	}
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(this);
}

void update(int L, int R, int w, int l, int r, int rt) {
	if (L <= l && R >= r) {
		add[rt] += w;
		lx[rt] += w;
		rx[rt] += w;
		return;
	}
	pushDown(rt);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, w, lch);
	if (R > m) update(L, R, w, rch);
	pushUp(this);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return msum[rt];
	}
	// pushDown(rt);
	int m = (l + r) >> 1;
	int ans = 0, ans1 = 0, ans2 = 0;
	if (m >= L) ans1 = query(L, R, lch);
	if (m < R) ans2 = query(L, R, rch);
	ans = max(ans1, ans2);
	if (rx[lef] < lx[rig]) {
		ans = max(ans, min(m - L + 1, rsum[lef]) + min(R - m, lsum[rig]));
	}
	return ans;
}

int main() {
	freopen("360.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		printf("Case #%d:\n", cas++);
		scanf("%d %d", &n, &q);
		buildTree(roo);
		char op[2];
		int a, b, w;
		for (int i = 0; i < q; i++) {
			scanf("%s%d%d", op, &a, &b);
			if (op[0] == 'a') {
				scanf("%d", &w);
				update(a, b, w, roo);
			} else {
				int ans = query(a, b, roo);
				printf("%d\n", ans);
			}
		}
	}


	return 0;
}
