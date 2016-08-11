#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)

const int MAXN = 100005;

struct Node{
	int h, pos;
	Node() {}
	Node(int c, int d) : h(c), pos(d) {}
	bool operator < (const Node &n) const {
		return h > n.h;
	}
};

struct Ret{
	int lmax, rmax, mmax;
	Ret() {}
	Ret(int a, int b, int c) : lmax(a), rmax(b), mmax(c) {}
};

int n, q, cnt = 0;
Node arr[MAXN];
int heights[MAXN];
int mmax[MAXN * 100], lmax[MAXN * 100], rmax[MAXN * 100];
int root[MAXN], ls[MAXN * 100], rs[MAXN * 100];

void insert(int x, int &y, int l, int r, int pos) {
	// cout << l << ' ' << r << endl;
	if (l > r) return;
	y = ++cnt;;
	if (l == r) {
		mmax[y] = lmax[y] = rmax[y] = 1;
		return;
	}
	ls[y] = ls[x];
	rs[y] = rs[x];
	int m = l + r >> 1;
	if (pos <= m) insert(ls[x], ls[y], l, m, pos);
	else insert(rs[x], rs[y], m + 1, r, pos);

	lmax[y] = lmax[ls[y]];
	rmax[y] = rmax[rs[y]];
	if (lmax[ls[y]] == m - l + 1) {
		lmax[y] = max(lmax[y], lmax[ls[y]] + lmax[rs[y]]);
	}
	if (rmax[rs[y]] == r - m) {
		rmax[y] = max(rmax[y], rmax[rs[y]] + rmax[ls[y]]);
	}
	mmax[y] = max(mmax[ls[y]], mmax[rs[y]]);
	mmax[y] = max(mmax[y], max(lmax[y], rmax[y]));
	mmax[y] = max(mmax[y], rmax[ls[y]] + lmax[rs[y]]);
}

Ret query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return Ret(lmax[rt], rmax[rt], mmax[rt]);
	}
	int m = l + r >> 1;
	Ret ret = Ret(0, 0, 0);
	Ret ll = Ret(0, 0, 0), rr = Ret(0, 0, 0);
	if (L <= m) {
		ll = query(L, R, l, m, ls[rt]);
	}
	if (R > m) {
		rr = query(L, R, m + 1, r, rs[rt]);
	}

	ret.lmax = ll.lmax;
	ret.rmax = rr.rmax;
	if (ll.lmax == m - max(l, L) + 1) {
		ret.lmax = max(ret.lmax, ll.lmax + rr.lmax);
	}
	if (rr.rmax == min(r, R) - m) {
		ret.rmax = max(ret.rmax, rr.rmax + ll.rmax);
	}
	ret.mmax = max(ll.mmax, rr.mmax);
	ret.mmax = max(ret.mmax, max(ret.lmax, ret.rmax));
	ret.mmax = max(ret.mmax, ll.rmax + rr.lmax);
	return ret;
}

int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].h);
		arr[i].pos = i;
	}
	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++) {
		insert(root[i - 1], root[i], 1, n, arr[i].pos);
	}

	int a, b, k;
	scanf("%d", &q);
	while (q--) {
		scanf("%d %d %d", &a, &b, &k);
		int l = 1, r = n;
		while (l < r) {
			int m = l + r >> 1;
			int len = query(a, b, 1, n, root[m]).mmax;
			if (len >= k) r = m;
			else l = m + 1;
		}
		printf("%d\n", arr[l].h);
	}

	
	return 0;
}