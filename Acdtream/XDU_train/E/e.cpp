#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 50005;

int T, n, m, q;
long long add[MAXN << 2];
long long mi[MAXN << 2];

void pushup(int rt) {
	mi[rt] = min(mi[lch], mi[rch]);
	if (mi[rt] < 0) mi[rt] = 0;
}

void pushdown(int rt) {
	if (add[rt]) {
		add[lch] += add[rt];
		add[rch] += add[rt];

		mi[lch] += add[rt];
		mi[lch] = max(mi[lch], 0ll);
		mi[rch] += add[rt];
		mi[rch] = max(mi[rch], 0ll);
		add[rt] = 0;
	}
}

void build(int l,int r,int rt) {
	add[rt] = 0;
	mi[rt] = 0;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(lson);
	build(rson);
}

int query(int l, int r, int rt) {
	if (l == r) return l;
	int mid = l + r >> 1;
	pushdown(rt);
	if (!mi[lch]) return query(lson);
	if (!mi[rch]) return query(rson);
	return n + 1;
}

void update(int l, int r, int rt, int idx, long long c) {
	if (l == r) {
		mi[rt] += c;
		return;
	}
	int mid = l + r >> 1;
	if (idx <= mid) update(lson, idx, c);
	else update(rson, idx, c);
	pushup(rt);
}

int t[MAXN], l[MAXN];
int main() {
	freopen("e.in", "r", stdin);
	cin >> T;
	for (int cas = 1; cas <= T; cas++) {
		printf("Case #%d:\n", cas);
		cin >> n >> m >> q;
		build(1, n, 1);
		int pret = 0;
		for (int i = 1; i <= q; i++) {
			scanf("%d %d", &t[i], &l[i]);
		}
		t[0] = t[1];
		for (int i = 1; i <= q; i++) {
			int past = t[i] - t[i - 1];
			add[1] -= past;
			mi[1] -= past;
			int idx = query(1, n, 1);
			if (idx == n + 1) {
				printf("Failed!\n");
			} else {
				printf("%d\n", idx);
				update(1, n, 1, idx, l[i] + m);

			}

		}

	}

	

	return 0;
}
