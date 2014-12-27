#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
#define roo 1, n, 1
#define this l, r, rt

using namespace std;

const int maxn = 50002;

int n, q;
long long sum[maxn << 2];
int arr[maxn];
long long add[maxn << 2];
int mark[maxn];
void pushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	sum[rt] %= 2333333;
}

long long calc(long long x) {
	long long ans = 1;
	long long base = 2;
	while (x) {
		if (x & 1) {
			ans *= base;
			ans %= 2333333;
		}
		base *= base;
		base %= 2333333;
		x >>= 1;
	}
	return ans;
}

void pushDown(int l, int r, int rt) {
	int m = r - l + 1;
	if (add[rt]) {
		add[rt] %= 2333333;
		add[rt << 1] += add[rt];
		add[rt << 1] %= 2333333;
		add[rt << 1 | 1] += add[rt];
		add[rt << 1 | 1] %= 2333333;
		sum[rt << 1] += add[rt] * (m - (m >> 1));
		sum[rt << 1] %= 2333333;
        sum[rt << 1 | 1] += add[rt] * (m >> 1);
        sum[rt << 1 | 1] %= 2333333;
        add[rt] = 0;
	}
}

void buildTree(int l, int r, int rt) {
	sum[rt] = 0;
	add[rt] = 0;
	if (l == r) {
		scanf("%I64d", &sum[rt]);
		arr[l] = sum[rt];
		return;
	}
	int m = l + r >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(rt);
}

long long query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	pushDown(this);
	int m = l + r >> 1;
	long long ans = 0;
	if (L <= m) ans += query(L, R, lch);
	ans %= 2333333;
	if (R > m) ans += query(L, R, rch);
	ans %= 2333333;
	return ans;
}

void update(int L, int R, int x, int l, int r, int rt) {
	if (L <= l && R >= r) {
		add[rt] += (long long)x;
		add[rt] %= 2333333;
		sum[rt] += (long long)x * (r - l + 1);
		sum[rt] %= 2333333;
		return;
	}
	pushDown(this);
	int m = l + r >> 1;
	if (L <= m) update(L, R, x, lch);
	if (R > m) update(L, R, x, rch);
	pushUp(rt);
}

void update2(int x, int l, int r, int rt) {
	if (l == r) {
		sum[rt] = arr[x];
		for (int i = 0; i < mark[x]; i++) {
			sum[rt] = (sum[rt] - 1) % 61020 + 1;
			sum[rt] = calc(sum[rt]);
		}
		return;
	}
	pushDown(this);
	int m = l + r >> 1;
	if (x <= m) update2(x, lch);
	if (x > m) update2(x, rch);
	pushUp(rt);
}

int main() {
	while (~scanf("%d %d", &n, &q)) {
		memset(mark, 0, sizeof(mark));
		buildTree(roo);
		int a, b, c, x;
		for (int i = 0; i < q; i++) {
			scanf("%d", &c);
			if (c == 1) {
				scanf("%d %d", &a, &b);
				printf("%I64d\n", query(a, b, roo) % 2333333);
			} else if (c == 3) {
				scanf("%d %d %d", &a, &b, &x);
				// x %= 2333333;
				update(a, b, x, roo);
			} else if (c == 2) {
				scanf("%d", &x);
				mark[x]++;
				update2(x, roo);
			}
		}
	}
	return 0;
}
