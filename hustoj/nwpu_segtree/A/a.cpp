#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch
#define this l, r, rt
#define MAXN 20005

using namespace std;

struct seg{
	int h, l, r;
	int pos;
	seg() {}
	seg(int a, int b, int c, int d) : h(a + 10000), l(b + 10000), r(c + 10000), pos(d) {}
	bool operator < (const seg &ss) const {
		if (h != ss.h) return h < ss.h;
		return pos > ss.pos;
	}
};

int n, ans = 0;
int cnt[MAXN << 2];
seg hor[MAXN];
seg ver[MAXN];

void pushup(int rt) {
	if (cnt[lch] == cnt[rch]) cnt[rt] = cnt[lch];
	else cnt[rt] = -1;
}

void pushdown(int rt) {
	if (cnt[rt] == -1) return;
	cnt[lch] = cnt[rt];
	cnt[rch] = cnt[rt];
}

void update(int L, int R, int pos, int l, int r, int rt) {
	int m = l + r >> 1;
	if (L <= l && r <= R) {
		if (cnt[rt] != -1) {
			cnt[rt] += pos;
			if (cnt[rt] == 1 && pos == 1 || cnt[rt] == 0 && pos == -1)
				ans += r - l + 1;
		} else {
			update(L, R, pos, lson);
			update(L, R, pos, rson);
			pushup(rt);
		}
		return;
	}
	pushdown(rt);
	if (m >= L) update(L, R, pos, lson);
	if (m < R) update(L, R, pos, rson);
	pushup(rt);
}

int main() {
	freopen("a.in", "r", stdin);
	while (~scanf("%d", &n)) {
		memset(cnt, 0, sizeof(cnt));
		ans = 0;
		int x1,  x2, y1, y2;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			hor[i << 1] = seg(y1, x1, x2, 1);
			hor[i << 1 | 1] = seg(y2, x1, x2, -1);
			ver[i << 1] = seg(x1, y1, y2, 1);
			ver[i << 1 | 1] = seg(x2, y1, y2, -1);
		}
		sort(hor, hor + (n << 1));
		sort(ver, ver + (n << 1));
		for (int i = 0; i < n << 1; i++) {
			update(hor[i].l, hor[i].r - 1, hor[i].pos, 0, 20000, 1);
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n << 1; i++) {
			update(ver[i].l, ver[i].r - 1, ver[i].pos, 0, 20000, 1);
		}
		cout << ans << endl;
	}

	return 0;
}
