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

using namespace std;

const int MAXN = 100005;

struct Line{
	int l, r, h;
	Line() {}
	Line(int a, int b, int c) : l(a), r(b), h(c) {}
	bool operator < (const Line &li) const {
		if (h != li.h) return h < li.h;
		return l < li.l;
	}
};

int T, n;
Line ver[MAXN], hor[MAXN];
int nv, nh;

int sum[MAXN << 4], add[MAXN << 4];
void PushUp(int rt) {
	sum[rt] = sum[lch] + sum[rch];
}
void PushDown(int rt, int m) {
	if (add[rt]) {
		add[lch] += add[rt];
		add[rch] += add[rt];
		sum[lch] += add[rt] * (m - (m >> 1));
		sum[rch] += add[rt] * (m >> 1);
		add[rt] = 0;
	}
}
void update(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) {
		add[rt]++;
		sum[rt] += (r - l + 1);
		return;
	}
	PushDown(rt , r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) update(lson, L, R);
	if (m < R) update(rson, L, R);
	PushUp(rt);
}

int query(int l, int r, int rt, int pos) {
	if (l == pos && r == pos) return sum[rt];
	int m = l + r >> 1;
	PushDown(rt , r - l + 1);
	if (pos <= m) return query(lson, pos);
	if (m < pos) return query(rson, pos);
}

set<int> ps;
map<int, int> has;

int cmp1(Line a, Line b) {
	if (a.l != b.l) return a.l < b.l;
	return a.r < b.r;
}

int cmp2(Line a, Line b) {
	if (a.r != b.r) return a.r < b.r;
	return a.l < b.l;
}

int main() {
	freopen("1006.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		nv = 0, nh = 0;
		int a, b, c, d;

		ps.clear();
		has.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			ps.insert(a), ps.insert(b), ps.insert(c), ps.insert(d);
			if (a > c) swap(a, c);
			if (b > d) swap(b, d);
			if (a == c) ver[++nv] = Line(b, d, a);
			if (b == d) hor[++nh] = Line(a, c, b);
		}
		int tot = 0;
		for (set<int>::iterator it = ps.begin(); it != ps.end(); it++) {
			has[*it] = ++tot;
		}

		sort(hor + 1, hor + nh + 1);



		int ans = 0;
		int now = 1;
		sort(ver + 1, ver + nv + 1, cmp1);
		for (int i = 0; i <= tot << 2; i++)
			sum[i] = add[i] = 0;
		for (int i = 1; i <= nh; i++) {
			while (now <= nv && has[hor[i].h] >= has[ver[now].l]) {
				// cout << has[hor[i].h] << endl;
				ans -= query(1, tot, 1, has[ver[now].h]);

				now++;
			}
			update(1, tot, 1, has[hor[i].l], has[hor[i].r]);
		}
		for (int i = now; i <= nv; i++)
			ans -= query(1, tot, 1, has[ver[i].h]);
		
		for (int i = 0; i <= tot << 2; i++)
			sum[i] = add[i] = 0;
		now = 1;
		sort(ver + 1, ver + nv + 1, cmp2);
		for (int i = 1; i <= nh; i++) {
			while (now < nv && has[hor[i].h] > has[ver[now].r]) {

				ans += query(1, tot, 1, has[ver[now].h]);
				now++;
			}
			update(1, tot, 1, has[hor[i].l], has[hor[i].r]);
		}
		for (int i = now; i <= nv; i++)
			ans += query(1, tot, 1, has[ver[i].h]);

		printf("%d\n", ans);
	}




	return 0;
}
