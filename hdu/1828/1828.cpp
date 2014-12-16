/*
ID:shijiey1
LANG:C++
PROG:picture
*/
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

const int MAXN = 20002;

struct SEG{
	int h, l, r;
	int pos;
	SEG() {}
	SEG(int a, int b, int c, int d) : l(a + 10000), r(b + 10000), h(c + 10000), pos(d) {}
	bool operator < (const SEG &ss) const {
		if (h != ss.h) return h < ss.h;
		return pos > ss.pos;
	}
}hor[MAXN], ver[MAXN];

int n, ans = 0;
int cnt[MAXN << 2];

void pushUp(int l, int r, int rt) {
	if (cnt[lef] == cnt[rig]) cnt[rt] = cnt[lef];
	else cnt[rt] = -1;
}

void pushDown(int rt)
{
	if (cnt[rt]==-1) return;
	cnt[lef]=cnt[rt];
	cnt[rig]=cnt[rt];
	return;
}

void update(int L, int R, int pos, int l, int r, int rt) {
	int m = l + r >> 1;
	if (L <= l && R >= r) {
		if (cnt[rt] != -1) {
			cnt[rt] += pos;
			if ((cnt[rt] == 1 && pos == 1) || (cnt[rt] == 0 && pos == -1)) {
				ans += r - l + 1;
			}
		} else {
			update(L, R, pos, lch);
			update(L, R, pos, rch);
			pushUp(this);
		}
		return;
	}
	pushDown(rt);
	if (L <= m) update(L, R, pos, lch);
	if (R > m) update(L, R, pos, rch);
	pushUp(this);
}

int main() {
	freopen("1828.in", "r", stdin);
	// freopen("picture.out", "w", stdout);
	while (~scanf("%d", &n)) {
		memset(cnt, 0, sizeof(cnt));
		int x1, y1, x2, y2;
		int mh = 0, mv = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			hor[mh++] = SEG(x1, x2, y1, 1);
			hor[mh++] = SEG(x1, x2, y2, -1);
			ver[mv++] = SEG(y1, y2, x1, 1);
			ver[mv++] = SEG(y1, y2, x2, -1);
		}
		sort(hor, hor + mh);
		sort(ver, ver + mv);
		for (int i = 0; i < mh; i++) {
			if (hor[i].l < hor[i].r) {
				//printf("%d %d %d\n", ans,hor[i].l, hor[i].r);
				update(hor[i].l, hor[i].r - 1, hor[i].pos, 0, 20000, 1);
			}
		}
		//cout << ans << endl;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < mv; i++) {
			// if (ver[i].l < ver[i].r) {
				update(ver[i].l, ver[i].r - 1, ver[i].pos, 0, 20000, 1);
			// }
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
