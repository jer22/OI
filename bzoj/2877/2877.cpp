#include <bits/stdc++.h>

#define p(i, j) (((i) - 1) * m + (j))
#define g(i, j) (((i) - 1) * ((m << 2) + 100) + (j))
#define MAXN 555555
#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

int n, m, sx, sy, q;
long long d[MAXN << 2], a[MAXN << 2], ss[MAXN << 4], d1[MAXN], d2[MAXN];
long long s[2][MAXN << 2];

long long gcd(long long a, long long b) {
	if (a<0) a=-a; if (b<0) b=-b; long long temp;
    while (b) {temp=b; b=a%b; a=temp;}
    return a;
}

void update(int k, int l, int r, int rt, int x, long long c) {
	if (l == r) {
		s[k][rt] = c;
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) update(k, lson, x, c);
	else update(k, rson, x, c);
	s[k][rt] = gcd(s[k][rt << 1], s[k][rt << 1 | 1]);
}

void upy(int rx, int f, int ry, int l, int r, int y, long long c) {
	if (l == r) {
		if (f) ss[g(rx, ry)] = c;
		else ss[g(rx, ry)] = gcd(ss[g(rx << 1, ry)], ss[g(rx << 1 | 1, ry)]);
		return;
	}
	int mid = l + r >> 1;
	if (y <= mid) upy(rx, f, ry << 1, l, mid, y, c);
	else upy(rx, f, ry << 1 | 1, mid + 1, r, y, c);
	ss[g(rx, ry)] = gcd(ss[g(rx, ry << 1)], ss[g(rx, ry << 1 | 1)]);
}

void upx(int l, int r, int rt, int x, int y, long long c) {
	if (l == r) {
		upy(rt, 1, 1, 1, m, y, c);
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) upx(lson, x, y, c);
	else upx(rson, x, y, c);
	upy(rt, 0, 1, 1, m, y, c);
}

long long query(int k, int l, int r, int rt, int L, int R) {
	if (L > R) return 0;
	if (L <= l && r <= R) return s[k][rt];
	int mid = l + r >> 1;
	long long t1 = 0, t2 = 0;
	if (L <= mid) t1 = query(k, lson, L, R);
	if (R > mid) t2 = query(k, rson, L, R);
	return gcd(t1, t2);
}

long long quy(int rx, int ry, int L, int R, int l, int r) {
	if (l <= L && R <= r) return ss[g(rx, ry)];
	int mid = L + R >> 1;
	long long t1 = 0, t2 = 0;
	if (l <= mid) t1 = quy(rx, ry << 1, L, mid, l, r);
	if (r > mid) t2 = quy(rx, ry << 1 | 1, mid + 1, R, l, r);
	return gcd(t1, t2);
}

long long qux(int rx, int L, int R, int l1, int r1, int l2, int r2) {
	if (l1 > r1 || l2 > r2) return 0;
	if (l1 <= L && r1 >= R) return quy(rx, 1, 1, m, l2, r2);
	int mid = L + R >> 1;
	long long t1 = 0, t2 = 0;
	if (l1 <= mid) t1 = qux(rx << 1, L, mid, l1, r1, l2, r2);
	if (r1 > mid) t2 = qux(rx << 1 | 1, mid + 1, R, l1, r1, l2, r2);
	return gcd(t1, t2);
}

int main() {
	scanf("%d %d", &n, &m);
	scanf("%d %d", &sx, &sy);
	scanf("%d", &q);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%lld", &d[p(i, j)]);
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			a[p(i, j)] = d[p(i, j)] + d[p(i + 1, j + 1)] - d[p(i + 1, j)] - d[p(i, j + 1)];
			upx(1, n, 1, i, j, a[p(i, j)]);
		}
	}
	for (int i = 1; i < n; i++) {
		d1[i] = d[p(i + 1, sy)] - d[p(i, sy)];
		update(1, 1, n, 1, i, d1[i]);
	}
	for (int i = 1; i < m; i++) {
		d2[i] = d[p(sx, i + 1)] - d[p(sx, i)];
		update(0, 1, m, 1, i, d2[i]);
	}
	int op, x1, y1, x2, y2;
	long long c;
	while (q--) {
		scanf("%d %d %d %d %d", &op, &x1, &y1, &x2, &y2);
		if (!op) {
			long long ans = gcd(d[p(sx, sy)], qux(1, 1, n, sx - x1, sx + x2 - 1, sy - y1, sy + y2 - 1));
			ans = gcd(ans, query(1, 1, n, 1, sx - x1, sx + x2 - 1));
			ans = gcd(ans, query(0, 1, m, 1, sy - y1, sy + y2 - 1));
			printf("%lld\n", ans);
		} else {
			scanf("%lld", &c);
			if (x1 != 1 && y1 != 1) upx(1, n, 1, x1 - 1, y1 - 1, a[p(x1 - 1, y1 - 1)] += c);
			if (x1 != 1 && y2 != m) upx(1, n, 1, x1 - 1, y2 , a[p(x1 - 1, y2)] -= c);
                if (x2 != n && y1 != 1) upx(1, n, 1, x2, y1 - 1, a[p(x2, y1 - 1)] -= c);
            if (x2 != n && y2 != m) upx(1, n, 1, x2, y2, a[p(x2, y2)] += c);
            if (y1 <= sy && y2 >= sy){
                if (x1 != 1) update(1, 1, n, 1, x1 - 1, d1[x1 - 1] += c);
                if (x2 != n) update(1, 1, n, 1, x2, d1[x2] -= c);
            }
            if (x1 <= sx && x2 >= sx){
                if (y1 != 1) update(0, 1, m, 1, y1 - 1, d2[y1 - 1] += c);
                if (y2 != m) update(0, 1, m, 1, y2, d2[y2] -= c);
            }
            if (x1 <= sx && x2 >= sx && y1 <= sy && y2 >= sy)
                d[p(sx, sy)] += c;
		}
	}
	return 0;
}
