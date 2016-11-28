#include <bits/stdc++.h>

#define sign(x) ((x) > 0 ? 1 : (x) < 0 ? -1 : 0)
#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 300005;


int n, q;
long long arr[MAXN];
long long val[MAXN];
int lmax[MAXN << 2], rmax[MAXN << 2], mmax[MAXN << 2];

void pushup(int l, int r, int rt) {
	int m = l + r >> 1;
	mmax[rt] = max(mmax[lch], mmax[rch]);
	lmax[rt] = lmax[lch];
	rmax[rt] = rmax[rch];
	if (val[m] && val[m + 1] && (sign(val[m]) >= sign(val[m + 1]))) {
		mmax[rt] = max(mmax[rt], lmax[rch] + rmax[lch]);
		if (lmax[lch] == m - l + 1) lmax[rt] = lmax[lch] + lmax[rch];
		if (rmax[rch] == r - m) rmax[rt] = rmax[rch] + rmax[lch];
	}
}

void build(int l, int r, int rt) {
	if (l > r) return;
	if (l == r) {
		lmax[rt] = rmax[rt] = mmax[rt] = (bool)val[l];
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(l, r, rt);
}

void update(int l, int r, int rt, int pos, long long v) {
	if (l == r) {
		val[pos] += v;
		lmax[rt] = rmax[rt] = mmax[rt] = bool(val[l]);
		return;
	}
	int m = l + r >> 1;
	if (pos <= m) update(lson, pos, v);
	else update(rson, pos, v);
	pushup(l, r, rt);
}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &arr[i]);
	for (int i = 1; i < n; i++)
		val[i] = arr[i + 1] - arr[i];
	build(1, n - 1, 1);
	scanf("%d", &q);
	int a, b;
	long long c;
	while (q--) {
		scanf("%d %d %lld", &a, &b, &c);
		if (n == 1) {
			cout << 1 << endl;
			continue;
		}
		if (a - 1) {
			update(1, n - 1, 1, a - 1, c);
		}
		if (b < n) {
			update(1, n - 1, 1, b, -c);
		}
		cout << mmax[1] + 1 << endl;
	}

	return 0;
}
