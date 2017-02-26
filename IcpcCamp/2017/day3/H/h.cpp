#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 100005;
const int PRECISION = 45;

double p[MAXN];
double sum[MAXN << 2][50];
void pushup(int rt) {
	for (int i = 1; i <= PRECISION; i++)
		sum[rt][i] = sum[lch][i] + sum[rch][i];
}
double mul[MAXN << 2];
void pushdown(int rt) {
	if (mul[rt] != 1.) {
		mul[lch] *= mul[rt];
		mul[rch] *= mul[rt];
		double f = 1.;
		for (int i = 1; i <= PRECISION; i++) {
			f *= mul[rt];
			sum[lch][i] *= f;
			sum[rch][i] *= f;
		}
		mul[rt] = 1.;
	}
}

void build(int l, int r, int rt) {
	mul[rt] = 1.;
	if (l == r) {
		double f = 1.;
		for (int i = 1; i <= PRECISION; i++) {
			f *= p[l];
			sum[rt][i] = f / i;
		}
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

double query(int L, int R, int l, int r, int rt) {
	double ans = 0.;
	if (L <= l && r <= R) {
		for (int i = 1; i <= PRECISION; i++)
			ans += sum[rt][i];
		return ans;
	}
	pushdown(rt);
	int m = l + r >> 1;
	if (L <= m) ans += query(L, R, lson);
	if (m < R) ans += query(L, R, rson);
	return ans;
}

void multi(int L, int R, double c, int l, int r, int rt) {
	if (L <= l && r <= R) {
		mul[rt] *= c;
		double f = 1.;
		for (int i = 1; i <= PRECISION; i++) {
			f *= c;
			sum[rt][i] *= f;
		}
		return;
	}
	pushdown(rt);
	int m = l + r >> 1;
	if (L <= m) multi(L, R, c, lson);
	if (m < R) multi(L, R, c, rson);
	pushup(rt);
}

int n, q;
int main() {
	while (~scanf("%d %d", &n, &q)) {
		for (int i = 1; i <= n; i++)
			scanf("%lf", &p[i]);
		build(1, n, 1);
		int op, a, b;
		double c;
		while (q--) {
			scanf("%d %d %d", &op, &a, &b);
			if (!op) {
				double ans = query(a, b, 1, n, 1);
				printf("-%.30lf\n", ans);
			} else {
				scanf("%lf", &c);
				multi(a, b, c, 1, n, 1);
			}
		}
	}


	return 0;
}
