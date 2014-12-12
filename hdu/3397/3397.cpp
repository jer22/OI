#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lef rt << 1
#define rig rt << 1 | 1
#define lch l, m, lef
#define rch m + 1, r, rig
#define roo 0, n - 1, 1
#define this l, r, rt

using namespace std;

const int MAXN = 100002;

int T;
int n, q;
int sum[MAXN << 2], lsum[MAXN << 2], rsum[MAXN << 2], msum[MAXN << 2];
int cover[MAXN << 2];
int Xor[MAXN << 2];

void fxor(int rt) {
	if (cover[rt] != -1) cover[rt] ^= 1;
	else Xor[rt] ^= 1;
}

void pushUp(int l, int r, int rt) {
	sum[rt] = sum[lef] + sum[rig];
	int m = (l + r) >> 1;
	lsum[rt] = (lsum[lef] == m - l + 1) ? (lsum[lef] + lsum[rig]) : lsum[lef];
	rsum[rt] = (rsum[rig] == r - m) ? (rsum[rig] + rsum[lef]) : rsum[rig];
	msum[rt] = max(max(msum[lef], msum[rig]), rsum[lef] + lsum[rig]);
}

void buildTree(int l, int r, int rt) {
	cover[rt] = -1;
	Xor[rt] = 0;
	if (l == r) {
		scanf("%d", &sum[rt]);
		lsum[rt] = rsum[rt] = msum[rt] = sum[rt];
		return;
	}
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(this);
}

void pushDown(int l, int r, int rt) {
	if (cover[rt] != -1) {
		cover[lef] = cover[rig] = cover[rt];
		int m = (l + r) >> 1;
		sum[lef] = lsum[lef] = rsum[lef] = msum[lef] = cover[rt] * (m - l + 1);
		sum[rig] = lsum[rig] = rsum[rig] = msum[rig] = cover[rt] * (r - m);
	}
	if (Xor[rt]) {
		fxor(lef);
		fxor(rig);
		Xor[rt] = 0;
	}
}

void update(int L, int R, int op, int l, int r, int rt) {

	if (L <= l && R >= r) {
		if (op != 2) {
			cover[rt] = op;
			Xor[rt] = 0;
			sum[rt] = lsum[rt] = rsum[rt] = msum[rt] = cover[rt] * (r - l + 1);
		} else {
			fxor(rt);
			sum[rt] = (r - l + 1) - sum[rt];
			
		}
		
		return;
	}
	if (l == r) return;
	pushDown(this);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, op, lch);
	if (R > m) update(L, R, op, rch);
	pushUp(this);
}

int query1(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	pushDown(this);
	int m = (l + r) >> 1;
	int ans = 0;
	if (L <= m) ans += query1(L, R, lch);
	if (R > m) ans += query1(L, R, rch);
	return ans;
}

int query2(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return msum[rt];
	}
	pushDown(this);
	int m = (l + r) >> 1;
	if (R <= m) return query2(L, R, lch);
	if (L > m) return query2(L, R, rch);
	int ans = max(query2(L, R, lch), query2(L, R, rch));

}

int main() {
	freopen("3397.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		buildTree(roo);
		int op, a, b;
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &op, &a, &b);
			if (op == 0 || op == 1 || op == 2) {
				update(a, b, op, roo);
				cout << sum[1] << endl;
			} else {
				if (op == 3) {
					// printf("%d\n", query1(a, b, roo));
				} else {
					// printf("%d\n", query2(a, b, roo));
				}
			}
		}
	}

	return 0;
}
