#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 200005;
const int MAXM = 7000005;
const int MAXD = 19;
const int MAXX = (1 << MAXD) - 1;

int n, m;
int arr[MAXN], root[MAXN], tot = 0, siz[MAXM], tr[MAXM][2];

void insert(int x, int &y, int l, int r, int num) {
	y = ++tot;
	tr[y][0] = tr[x][0], tr[y][1] = tr[x][1];
	siz[y] = siz[x] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (num <= mid) insert(tr[x][0], tr[y][0], l, mid, num);
	else insert(tr[x][1], tr[y][1], mid + 1, r, num);
}

int query2(int x, int y, int L, int R, int l, int r) {
	if (L <= l && r <= R) return siz[y] - siz[x];
	int mid = l + r >> 1;
	int ans = 0;
	if (mid >= L) ans += query2(tr[x][0], tr[y][0], L, R, l, mid);
	if (mid < R) ans += query2(tr[x][1], tr[y][1], L, R, mid + 1, r);
	return ans;
}

int query(int d, int expect, int offset, int x, int y, int l, int r) {
	if (l == r) return l ^ expect;
	int mid = l + r >> 1;
	if ((expect >> d) & 1) {
		if (query2(x, y, max(0, l - offset), max(0, mid - offset), 0, MAXX))
			return query(d - 1, expect, offset, x, y, l, mid);
		else return query(d - 1, expect, offset, x, y, mid + 1, r);
	} else {
		if (query2(x, y, max(0, mid + 1 - offset), max(0, r - offset), 0, MAXX))
			return query(d - 1, expect, offset, x, y, mid + 1, r);
		else return query(d - 1, expect, offset, x, y, l, mid);
	}
}

int main() {
	freopen("4571.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		insert(root[i - 1], root[i], 0, MAXX, arr[i]);
	}
	for (int i = 0, e, o, l, r; i < m; i++) {
		scanf("%d %d %d %d", &e, &o, &l, &r);
		printf("%d\n", query(MAXD - 1, e, o, root[l - 1], root[r], 0, MAXX));
	}

	return 0;
}
