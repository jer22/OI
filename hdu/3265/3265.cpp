#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lef rt << 1
#define rig rt << 1 | 1
#define lch l, m, lef
#define rch m + 1, r, rig
#define this l, r, rt

using namespace std;

const int MAXN = 55555;

struct Line{
	int h, l, r, pos;
	Line() {}
	Line(int a, int b, int c, int d) : l(a), r(b), h(c), pos(d) {}
	bool operator < (const Line &line) const {
		return h < line.h;
	}
}seg[MAXN << 3];

int n;
int cover[MAXN << 4], sum[MAXN << 4];
int X[MAXN << 2];

void pushUp(int l, int r, int rt) {
	if (cover[rt] > 0) sum[rt] = X[r + 1] - X[l];
	else if (l == r) sum[rt] = 0;
	else sum[rt] = sum[lef] + sum[rig];
}

void update(int L, int R, int pos, int l, int r, int rt) {
	int m = l + r >> 1;
	if (L <= l && R >= r) {
		cover[rt] += pos;
		pushUp(this);
		return;
	}
	if (L <= m) update(L, R, pos, lch);
	if (R > m) update(L, R, pos, rch);
	pushUp(this);
}

int get(int key, int k) {
	int l = 0, r = k;
	while (l <= r) {
		int m = l + r >> 1;
		if (X[m] == key) return m;
		else if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

int main() {
	freopen("3265.in", "r", stdin);
	while (~scanf("%d", &n) && n) {
		int x1, y1, x2, y2, x3, y3, x4, y4;
		memset(cover, 0, sizeof(cover));
		memset(sum, 0, sizeof(sum));
		int m = 0, k = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
			X[k++] = x1; X[k++] = x2; X[k++] = x3; X[k++] = x4;
			seg[m++] = Line(x1, x3, y1, 1);
			seg[m++] = Line(x1, x3, y2, -1);
			seg[m++] = Line(x3, x4, y1, 1);
			seg[m++] = Line(x3, x4, y3, -1);
			seg[m++] = Line(x3, x4, y4, 1);
			seg[m++] = Line(x3, x4, y2, -1);
			seg[m++] = Line(x4, x2, y1, 1);
			seg[m++] = Line(x4, x2, y2, -1);
		}
		sort(seg, seg + m);
		sort(X, X + k);
		k = unique(X, X + k) - X - 1;
		long long res = 0;
		for (int i = 0; i < m - 1; i++) {
			int l = get(seg[i].l, k);
			int r = get(seg[i].r, k) - 1;
			if (l <= r)
				update(l, r, seg[i].pos, 0, k, 1);
			res += 1ll * (long long)(seg[i + 1].h - seg[i].h) * (long long)sum[1];
			// cout << res << endl;
		}
		printf("%I64d\n", res);
	}


	return 0;
}
