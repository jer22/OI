#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch
#define this l, r, rt

using namespace std;

const int MAXN = 1005;

struct Seg{
	int h, l, r;
	int pos;
	Seg() {}
	Seg(int a, int b, int c, int d) : l(a), r(b), h(c), pos(d) {}
	bool operator < (const Seg &ss) const {
		if (h != ss.h) return h < ss.h;
		return pos > ss.pos;
	}
}hor[MAXN << 1];

int T, n, np;
double rects[MAXN][4];
set<double> p;
double has[MAXN << 2];
map<double, int> m;

int cnt[100005 << 2];
double sum[100005 << 2];
double cro[100005 << 2];

void pushup(int l, int r, int rt) {
	if (cnt[rt]) sum[rt] = has[r + 1] - has[l]; // covered over 1 time
	else if (l == r) sum[rt] = 0; // leaf
	else sum[rt] = sum[lch] + sum[rch];

	if (cnt[rt] >= 2) cro[rt] = has[r + 1] - has[l];
	else if (l == r) cro[rt] = 0;
	else if (cnt[rt] == 1) cro[rt] = sum[lch] + sum[rch];
	else cro[rt] = cro[lch] + cro[rch];
}

void update(int L, int R, int pos, int l, int r, int rt) {
	int m = l + r >> 1;
	if (L <= l && r <= R) {
		cnt[rt] += pos;
		pushup(this);
		return;
	}
	if (L <= m) update(L, R, pos, lson);
	if (m < R) update(L, R, pos, rson);
	pushup(this);
}

int main() {
	freopen("1255.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		double x1, x2, y1, y2;
		p.clear();
		np = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &rects[i][0], &rects[i][1], &rects[i][2], &rects[i][3]);
			p.insert(rects[i][0]);
			p.insert(rects[i][1]);
			p.insert(rects[i][2]);
			p.insert(rects[i][3]);
		}
		// sort(p, p + (n << 2));
		memset(has, 0, sizeof(has));
		m.clear();
		for (set<double>::iterator it = p.begin(); it != p.end(); it++) {
			has[++np] = *it;
			m[*it] = np;
		}
		for (int i = 0; i < n; i++) {
			hor[i << 1] = Seg(m[rects[i][0]], m[rects[i][2]], m[rects[i][1]], 1);
			hor[i << 1 | 1] = Seg(m[rects[i][0]], m[rects[i][2]], m[rects[i][3]], -1);
		}
		sort(hor, hor + (n << 1));
		memset(cnt, 0, sizeof(cnt));
		memset(sum, 0, sizeof(sum));
		memset(cro, 0, sizeof(cro));
		double ans = 0.0;
		for (int i = 0; i < (n << 1) - 1; i++) {
			update(hor[i].l, hor[i].r - 1, hor[i].pos, 0, 100000, 1);
			ans += cro[1] * (has[hor[i + 1].h] - has[hor[i].h]);
			// cout << has[hor[i].h] << ' '  << sum[1] << endl;
		}
		ans *= 100;
		ans += 0.5;
		int r = (int)ans;
		printf("%.2lf\n", (double)r / 100);
	}


	return 0;
}
