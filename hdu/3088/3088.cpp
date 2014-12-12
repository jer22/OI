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
int num[MAXN];
int lsum[MAXN << 2], rsum[MAXN << 2], msum[MAXN << 2];

void pushUp(int l, int r, int rt) {
	lsum[rt] = lsum[lef];
	rsum[rt] = rsum[rig];
	msum[rt] = max(msum[lef], msum[rig]);
	int m = (l + r) >> 1;
	int len = r - l + 1;
	if (num[m] < num[m + 1]) {
		if (lsum[rt] == (len - (len >> 1))) lsum[rt] += lsum[rig];
		if (rsum[rt] == (len >> 1)) rsum[rt] += rsum[lef];
		msum[rt] = max(msum[rt], rsum[lef] + lsum[rig]);
	}
}

void buildTree(int l, int r, int rt) {
	if (l == r) {
		lsum[rt] = rsum[rt] = msum[rt] = 1;
		return;
	}
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(this);
}

void update(int p, int l, int r, int rt) {
	if (l == r) return;
	int m = (l + r) >> 1;
	if (p <= m) update(p, lch);
	else update(p, rch);
	pushUp(this);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) return msum[rt];
	int m = (l + r) >> 1;
	if (R <= m) return query(L, R, lch);
	if (L > m) return query(L, R, rch);
	int ans = max(query(L, R, lch), query(L, R, rch));
	if (num[m] < num[m + 1]) {
		ans = max(min(rsum[lef], m - L + 1) + min(lsum[rig], R - m), ans);
	}
	return ans;
}

int main() {
	freopen("3088.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; i++) scanf("%d", &num[i]);
		buildTree(roo);
		char ch[4];
		int a, b;
		for (int i = 1; i <= q; i++) {
			scanf("%s%d%d", ch, &a, &b);
			if (ch[0] == 'U') {
				num[a + 1] = b;
				update(a + 1, roo);
			} else {
				printf("%d\n", query(a + 1, b + 1, roo));
			}
		}
	}


	return 0;
}
