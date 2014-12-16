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

const int MAXN = 2111;

struct Line{
	double h, l, r;
	int pos;
	Line() {}
	Line(double a, double b, double c, int d) : l(a), r(b), h(c), pos(d) {}
	bool operator < (const Line &line) const {
		return h < line.h;
	}
}ss[MAXN];

int n;
double X[MAXN];
int cnt[MAXN << 2];
double sum[MAXN << 2];

int get(double key, int k) {
	int l = 0, r = k - 1;
	while (l <= r) {
		int m = l + r >> 1;
		if (X[m] == key) return m;
		if (X[m] < key) l = m + 1;
		else r = m - 1;
	}
	return -1;
}

void pushUp(int l, int r, int rt) {
	if (cnt[rt]) sum[rt] = X[r + 1] - X[l];
	else if (l == r) sum[rt] = 0;
	else sum[rt] = sum[lef] + sum[rig];
}

void update(int L, int R, int w, int l, int r, int rt) {
	if (L <= l && R >= r) {
		cnt[rt] += w;
		pushUp(this);
		return;
	}
	int m = l + r >> 1;
	if (L <= m) update(L, R, w, lch);
	if (R > m) update(L, R, w, rch);
	pushUp(this);
}

int main() {
	freopen("1542.in", "r", stdin);
	int cas = 1;
	while (~scanf("%d", &n) && n) {
		double a, b, c, d;
		int m = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
			X[m] = a;
			ss[m++] = Line(a, c, b, 1);
			X[m] = c;
			ss[m++] = Line(a, c, d, -1);
		}
		sort(X, X + m);
		sort(ss, ss + m);
		int k = 1;
		for (int i = 1; i < m; i++) {
			if (X[i] != X[i - 1]) X[k++] = X[i];
		}
		memset(cnt, 0, sizeof(cnt));
		memset(sum, 0, sizeof(sum));
		double res = 0;
		for (int i = 0; i < m - 1; i++) {
			int l = get(ss[i].l, k);
			int r = get(ss[i].r, k) - 1;
			// cout << l << ' ' << r << endl;
			if (l <= r) update(l, r, ss[i].pos, 0, k - 1, 1);
			res += sum[1] * (ss[i + 1].h - ss[i].h);
			// cout << res;
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n", cas++, res);
	}

	return 0;
}
