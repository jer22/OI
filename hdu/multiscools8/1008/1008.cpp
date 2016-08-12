#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch
#define LL long long

using namespace std;

const int MAXN = 100005;

LL read()
{
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

LL add[MAXN << 2], sum[MAXN << 2], ma[MAXN << 2];

int T, n, q;

void pushup(int rt) {
	sum[rt] = sum[lch] + sum[rch];
	ma[rt] = max(ma[lch], ma[rch]);
}

void pushdown(int rt,int m) {
	if (add[rt]) {
		add[lch] += add[rt];
		add[rch] += add[rt];
		sum[lch] += add[rt] * (m - (m >> 1));
		sum[rch] += add[rt] * (m >> 1);
		ma[lch] += add[rt];
		ma[rch] += add[rt];
		add[rt] = 0;
	}
}

void build(int l, int r, int rt) {
	add[rt] = 0;
	if (l == r) {
		sum[rt] = read();
		ma[rt] = sum[rt];
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void addon(int L,int R,int c,int l,int r,int rt) {
	if (L <= l && r <= R) {
		add[rt] += (LL)c;
		sum[rt] += (LL)c * (LL)(r - l + 1);
		ma[rt] += (LL)c;
		return;
	}
	pushdown(rt , r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) addon(L , R , c , lson);
	if (m < R) addon(L , R , c , rson);
	pushup(rt);
}

LL query_max(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return ma[rt];
	}
	pushdown(rt , r - l + 1);
	int m = l + r >> 1;
	LL ans = 0;
	if (L <= m) ans = max(ans, query_max(L, R, lson));
	if (m < R) ans = max(ans, query_max(L, R, rson));
	return ans;
}

void update_sqrt(int L, int R, int l, int r, int rt) {
	if (l == r) {
		sum[rt] = (LL)sqrt(sum[rt]);
		ma[rt] = sum[rt];
		return;
	}
	pushdown(rt , r - l + 1);
	int m = l + r >> 1;
	if (L <= m) {
		if (ma[lch] > 1) update_sqrt(L, R, lson);
	}
	if (m < R) {
		if (ma[rch] > 1) update_sqrt(L, R, rson);
	}

	pushup(rt);
}

LL query_sum(int L,int R,int l,int r,int rt) {
	if (L <= l && r <= R) {
		return sum[rt];
	}
	pushdown(rt , r - l + 1);
	int m = (l + r) >> 1;
	LL ret = 0;
	if (L <= m) ret += query_sum(L , R , lson);
	if (m < R) ret += query_sum(L , R , rson);
	return ret;
}

int main() {
	freopen("1008.in", "r", stdin);
	freopen("1008.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		build(1, n, 1);
		int op, a, b, c;
		while (q--) {
			op = read();
			a = read();
			b = read();
			// scanf("%d %d %d", &op, &a, &b);
			if (op == 1) {
				c = read();
				addon(a, b, c, 1, n, 1);
			} else if (op == 2) {
				if (query_max(a, b, 1, n, 1) > 1ll) {
					update_sqrt(a, b, 1, n, 1);
				}
			} else {
				printf("%lld\n", query_sum(a, b, 1, n, 1));
			}
		}

	}





	return 0;
}
