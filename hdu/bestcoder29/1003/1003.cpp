#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

int n, q;
int mi[400005], ma[400005];
long long sum[400005];

void pushUp(int rt) {
	mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
	ma[rt] = max(ma[rt << 1], ma[rt << 1 | 1]);
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void build(int l, int r, int rt) {
	if (l == r) {
		scanf("%lld", &sum[rt]);
		mi[rt] = ma[rt] = sum[rt];
		return;
	}
	int m = l + r >> 1;
	build(lch);
	build(rch);
	pushUp(rt);
}

int qmin(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return mi[rt];
	}
	int m = l + r >> 1;
	int ans1 = 0x3f3f3f3f;
	int ans2 = 0x3f3f3f3f;
	if (L <= m) ans1 = qmin(L, R, lch);
	if (R > m) ans2 = qmin(L, R, rch);
	return min(ans1, ans2);
}

int qmax(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return ma[rt];
	}
	int m = l + r >> 1;
	int ans1 = 0;
	int ans2 = 0;
	if (L <= m) ans1 = qmax(L, R, lch);
	if (R > m) ans2 = qmax(L, R, rch);
	return max(ans1, ans2);
}

long long qsum(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	int m = l + r >> 1;
	long long ans = 0;
	if (L <= m) ans += qsum(L, R, lch);
	if (R > m) ans += qsum(L, R, rch);
	return ans;
}

int main() {
	freopen("1003.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		memset(mi, 0, sizeof(mi));
		memset(ma, 0, sizeof(ma));
		memset(sum, 0, sizeof(sum));
		build(1, n, 1);
		int a, b;
		for (int i = 1; i <= q; i++) {
			scanf("%d %d", &a, &b);
			int t = b - a + 1;
			long long x;
			x = t;
			x *= (1 + t);
			x /= 2;
			if (qmin(a, b, 1, n, 1) == 1 && qmax(a, b, 1, n, 1) == b - a + 1 && qsum(a, b, 1, n, 1) == x) {
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
		}
	}


	return 0;
}
