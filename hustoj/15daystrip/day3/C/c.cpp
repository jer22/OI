#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l , m , lch
#define rson m + 1 , r , rch

using namespace std;

const int MAXN = 100005;

int n, q;
long long p;
long long add[MAXN << 2], arr[MAXN];
long long sum[MAXN << 2], mul[MAXN << 2];

void pushup(int l, int r, int rt) {	
	sum[rt] = (sum[lch] + sum[rch]) % p;
}
void build(int l, int r, int rt) {
	add[rt] = 0;
	mul[rt] = 1;
	if (l == r) {
		sum[rt] = arr[l];
		sum[rt] %= p;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(l, r, rt);
}
void pushdown(int l, int r, int rt) {	
	if (mul[rt] != 1) {
		(mul[lch] *= mul[rt]) %= p;
		(sum[lch] *= mul[rt]) %= p;
		(add[lch] *= mul[rt]) %= p;

		(mul[rch] *= mul[rt]) %= p;
		(sum[rch] *= mul[rt]) %= p;
		(add[rch] *= mul[rt]) %= p;
		mul[rt] = 1;
	}
	if (add[rt]) {
		int m = r - l + 1;
		(add[lch] += add[rt]) %= p;
		(sum[lch] += add[rt] * (long long)(m - (m >> 1))) %= p;

		(add[rch] += add[rt]) %= p;
		(sum[rch] += add[rt] * (long long)(m >> 1)) %= p;
		add[rt] = 0;
	}
}	

void mult(int l, int r, int rt, int L, int R, int c) {	
	if (L <= l && r <= R) {
		(mul[rt] *= (long long)c) %= p;
		(sum[rt] *= (long long)c) %= p;
		(add[rt] *= (long long)c) %= p;
		return;
	}
	pushdown(l, r, rt);
	int m = l + r >> 1;
	if (L <= m) mult(lson, L, R, c);
	if (m < R) mult(rson, L, R, c);
	pushup(l, r, rt);
}

void addon(int l, int r, int rt, int L, int R, int c) {
	if (L <= l && r <= R) {
		(add[rt] += (long long)c) %= p;
		(sum[rt] += (long long)c * (long long)(r - l + 1)) %= p;
		return;
	}
	pushdown(l, r, rt);
	int m = l + r >> 1;
	if (L <= m) addon(lson, L, R, c);
	if (m < R) addon(rson, L, R, c);
	pushup(l, r, rt);
}

long long query(int l, int r, int rt, int L, int R) {
	if (L <= l && r <= R) {
		// cout << l << ' ' << r << ' ' << sum[rt] << endl;
		return sum[rt];
	}
	pushdown(l, r, rt);
	int m = l + r >> 1;
	long long ret = 0;
	if (L <= m) (ret += query(lson, L , R)) %= p;
	if (m < R) (ret += query(rson, L , R)) %= p;
	return ret;
}

int main() {
	cin >> n >> p;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	scanf("%d", &q);
	build(1, n, 1);
	int op, l, r, c;
	while (q--) {
		scanf("%d %d %d", &op, &l, &r);
		if (op == 1) {
			scanf("%d", &c);
			c %= p;
			mult(1, n, 1, l, r, c);
		} else if (op == 2) {
			scanf("%d", &c);
			c %= p;
			addon(1, n, 1, l, r, c);
		} else if (op == 3) {
			long long ans = query(1, n, 1, l, r) % p;
			printf("%lld\n", ans);
		}
	}


	return 0;
}
