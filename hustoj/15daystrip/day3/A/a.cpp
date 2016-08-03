#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 50005;
const int INF = 0x3f3f3f3f;

struct Node {
	int sum, rmax, mmax, lmax;
	Node() {}
	Node(int a, int b, int c, int d) : lmax(a), rmax(b), mmax(c), sum(d) {}
};

int n, q;
int arr[MAXN];
int mmax[MAXN << 2], lmax[MAXN << 2], rmax[MAXN << 2], sum[MAXN << 2];

void pushup(int l, int r, int rt) {
	int m = l + r >> 1;
	sum[rt] = sum[lch] + sum[rch];
	lmax[rt] = max(lmax[lch], sum[lch] + lmax[rch]);
	rmax[rt] = max(rmax[rch], sum[rch] + rmax[lch]);

	mmax[rt] = max(mmax[lch], mmax[rch]);
	mmax[rt] = max(mmax[rt], max(lmax[rt], rmax[rt]));
	mmax[rt] = max(mmax[rt], lmax[rch] + rmax[lch]);
}

void build(int l, int r, int rt) {
	if (l == r) {
		mmax[rt] = lmax[rt] = rmax[rt] = sum[rt] = arr[l];
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(l, r, rt);
}

Node query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) {
		return Node(lmax[rt], rmax[rt], mmax[rt], sum[rt]);
	}
	int m = l + r >> 1;
	Node ans = Node();
	Node ln = Node(-INF, -INF, -INF, 0);
	Node rn = Node(-INF, -INF, -INF, 0);
	if (L <= m) ln = query(lson, L, R);
	if (m < R) rn = query(rson, L, R);
	ans.sum = ln.sum + rn.sum;
	ans.lmax = max(ln.lmax, ln.sum + rn.lmax);
	ans.rmax = max(rn.rmax, rn.sum + ln.rmax);

	ans.mmax = max(ln.mmax, rn.mmax);
	ans.mmax = max(ans.mmax, max(ans.lmax, ans.rmax));
	ans.mmax = max(ans.mmax, ln.rmax + rn.lmax);

	return ans;
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	build(1, n, 1);
	scanf("%d", &q);
	int l, r;
	while (q--) {
		scanf("%d %d", &l, &r);
		Node ans = query(1, n, 1, l, r);
		printf("%d\n", ans.mmax);

	}

	return 0;
}
