#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, lef
#define rch m + 1, r, rig
#define lef rt << 1
#define rig rt << 1 | 1
#define roo 1, n, 1

using namespace std;

const int MAXN = 50002;

int n, q;
int msum[MAXN << 2], lsum[MAXN << 2], rsum[MAXN << 2];
int cover[MAXN << 2];
void buildTree(int l, int r, int rt) {
	cover[rt] = -1;
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	if (l == r) return;
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
}

void pushUp(int l, int r, int rt) {
	int m = (l + r) >> 1;
	lsum[rt] = (lsum[lef] == m - l + 1) ? (m - l + 1 + lsum[rig]) : lsum[lef];
	rsum[rt] = (rsum[rig] == r - m) ? (r - m + rsum[lef]) : rsum[rig];
	msum[rt] = max(rsum[lef] + lsum[rig], max(msum[lef], msum[rig]));
}

void pushDown(int l, int r, int rt) {
	if (cover[rt] != -1) {
		cover[lef] = cover[rig] = cover[rt];
		int m = (l + r) >> 1;
		msum[lef] = lsum[lef] = rsum[lef] = cover[rt] * (m - l + 1);
		msum[rig] = lsum[rig] = rsum[rig] = cover[rt] * (r - m);
		cover[rt] = -1;
	}
}

void update(int L, int R, int w, int l, int r, int rt) {
	if (L <= l && R >= r) {
		cover[rt] = w;
		msum[rt] = lsum[rt] = rsum[rt] = w * (r - l + 1);
		return;
	}
	pushDown(l, r, rt);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, w, lch);
	if (R > m) update(L, R, w, rch);
	pushUp(l, r, rt);
}

int query(int w, int l, int r, int rt) {
	if (l == r) return l;
	pushDown(l, r, rt);
	int m = (l + r) >> 1;
	if (msum[lef] >= w) return query(w, lch);
	else if (rsum[lef] + lsum[rig] >= w) return m - rsum[lef] + 1;
	else return query(w, rch);
}

int main() {
	freopen("3667.in", "r", stdin);
	scanf("%d %d", &n, &q);
	buildTree(roo);
	int t;
	int a, b;
	for (int i = 0; i < q; i++) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &a);
			if (msum[1] < a) printf("0\n");
			else {
				int ans = query(a, roo);
				printf("%d\n", ans);
				update(ans, ans + a - 1, 0, roo);
			}
		} else {
			scanf("%d %d", &a, &b);
			update(a, a + b - 1, 1, roo);
		}
	}

	return 0;
}
