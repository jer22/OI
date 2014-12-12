#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define root 0, MAXN << 1, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 8002;

struct Seg{
	int l, r, x, id;
	bool operator < (const Seg &s) const {
		return x < s.x;
	}
}seg[MAXN];

int T, n;
int color[MAXN << 3];
bool mark[MAXN][MAXN];

void pushDown(int rt) {
	if (color[rt]) {
		color[rt << 1] = color[rt << 1 | 1] = color[rt];
		color[rt] = 0;
	}
}

void query(int L, int R, int id, int l, int r, int rt) {
	if (color[rt]) {
		mark[id][color[rt]] = true;
		return;
	}
	if (l == r) return;
	int m = (l + r) >> 1;
	if (L <= m) query(L, R, id, lch);
	if (R > m) query(L, R, id, rch);
}

void update(int L, int R, int c, int l, int r, int rt) {
	if (L <= l && R >= r) {
		color[rt] = c;
		return;
	}
	pushDown(rt);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, c, lch);
	if (R > m) update(L, R, c, rch);
}

int main() {
	freopen("1436.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &seg[i].l, &seg[i].r, &seg[i].x);
			seg[i].id = i;
		}
		sort(seg + 1, seg + n + 1);
		memset(color, 0, sizeof(color));
		memset(mark, false, sizeof(mark));
		for (int i = 1; i <= n; i++) {
			int l = seg[i].l << 1;
			int r = seg[i].r << 1;
			query(l, r, seg[i].id, root);
			update(l, r, seg[i].id, root);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (mark[i][j])
				for (int k = 1; k <= n; k++)
					if (mark[i][k] && mark[j][k]) ans++;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}
