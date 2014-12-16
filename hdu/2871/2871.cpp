#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

#define lef rt << 1
#define rig rt << 1 | 1
#define lch l, m, lef
#define rch m + 1, r, rig
#define roo 1, n, 1
#define this l, r, rt

using namespace std;

const int MAXN = 50002;

int n, q;
int msum[MAXN << 2], lsum[MAXN << 2], rsum[MAXN << 2], tree[MAXN << 2], lu[MAXN << 2], ru[MAXN << 2];
int cover[MAXN << 2];

void pushUp(int l, int r, int rt) {
	int m = (l + r) >> 1;
	msum[rt] = max(max(msum[lef], msum[rig]), rsum[lef] + lsum[rig]);
	lsum[rt] = lsum[lef] + (lsum[lef] == m - l + 1 ? lsum[rig] : 0);
    rsum[rt] = rsum[rig] + (rsum[rig] == r - m ? rsum[lef] : 0);
    tree[rt] = tree[lef] + tree[rig];
}

void pushDown(int l, int r, int rt) {
	if (cover[rt] != -1) {
		int m = (l + r) >> 1;
		cover[lef] = cover[rig] = cover[rt];
		tree[lef] = tree[rig] = 0;
		msum[lef] = lsum[lef] = rsum[lef] = (cover[rt] ? 0 : m - l + 1);
		msum[rig] = lsum[rig] = rsum[rig] = (cover[rt] ? 0 : r - m);
		if (cover[rt])
			lu[lef] = lu[rig] = lu[rt], ru[lef] = ru[rig] = ru[rt];
		cover[rt] = -1;
	}
}

void buildTree(int l, int r, int rt) {
	cover[rt] = -1;
	tree[rt] = 0;
	msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;
	if (l == r) return;
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
}

void update(int L, int R, int w, int l, int r, int rt) {
	int m = (l + r) >> 1;
	if (L <= l && R >= r) {
		cover[rt] = w;
		tree[rt] = 0;
		msum[rt] = lsum[rt] = rsum[rt] = (w ? 0 : r - l + 1);
		if (w) {
			lu[rt] = L;
			ru[rt] = R;
			if (l == L) {
				if (l != r) {
					pushDown(this);
					update(L, R, w, lch);
					pushUp(this);
				} else tree[rt] = 1;
			}
		}
		return;
	}
	pushDown(this);
	if (m >= L) update(L, R, w, lch);
	if (m < R) update(L, R, w, rch);
	pushUp(this);
}

int query(int l, int r, int rt, int x, int &L, int &R) {
	int m = (l + r) >> 1;
	if (l == r) {
		if (!msum[rt]) {
			L = lu[rt];
			R = ru[rt];
			return 1;
		}
		return 0;
	}
	pushDown(this);
	if (x <= m) return query(lch, x, L, R);
	else return query(rch, x, L, R);
}

int queryLen(int l, int r, int rt, int x) {
	int m = (l + r) >> 1;
	if (l == r) return l;
	pushDown(this);
	if (msum[lef] >= x) return queryLen(lch, x);
	else if (rsum[lef] + lsum[rig] >= x) return m - rsum[lef] + 1;
	else return queryLen(rch, x);
}

void free(int x) {
	int L, R;
	if (query(roo, x, L, R)) {
		printf("Free from %d to %d\n", L, R);
		update(L, R, 0, roo);
	} else printf("Reject Free\n");
}

void reset() {
	cover[1] = tree[1] = 0;
	msum[1] = rsum[1] = lsum[1] = n;
	printf("Reset Now\n");
}

void newUnit(int x) {
	int ans = queryLen(roo, x);
	printf("New at %d\n", ans);
	update(ans, ans + x - 1, 1, roo);
}

int getunit(int l, int r, int rt, int k) {
	int m = (l + r) >> 1;
	if (l == r) return lu[rt];
	pushDown(this);
	if (k <= tree[lef]) return getunit(lch, k);
	else return getunit(rch, k - tree[lef]);
}

void solve() {
	char op[6];
	int x;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		if (op[0] == 'R') reset();
		else if (op[0] == 'N') {
			scanf("%d", &x);
			if (msum[1] < x) printf("Reject New\n");
			else newUnit(x);
		} else if (op[0] == 'F') {
			scanf("%d", &x);
			free(x);
		} else {
			scanf("%d", &x);
			if (tree[1] < x) printf("Reject Get\n");
			else printf("Get at %d\n", getunit(roo, x));
		}
	}
}

int main() {
	freopen("2871.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		buildTree(roo);
		solve();
		printf("\n");
	}

	return 0;
}
