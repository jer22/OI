#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lson l, m, lc
#define rson m + 1, r, rc
#define lc (rt << 1)
#define rc (rt << 1 | 1)

using namespace std;

const int MAXN = 100002;

int T;
int n, q;
char str[MAXN];
int sum[MAXN << 2];
int Max[MAXN << 2];
int Min[MAXN << 2];
int cover[MAXN << 2];
int Xor[MAXN << 2];

void fxor(int rt) {
	if (cover[rt]) cover[rt] = -cover[rt];
	else Xor[rt] ^= 1;
}

void pushUP(int rt) { 
	sum[rt] = sum[lc] + sum[rc];
	Max[rt] = max(Max[lc], sum[lc] + Max[rc]);
	Min[rt] = min(Min[lc], sum[lc] + Min[rc]);
}

void pushDown(int rt, int len) {
	if (cover[rt]) {
		cover[lc] = cover[rc] = cover[rt];
		sum[lc] = cover[rt] * (len - (len >> 1));
		sum[rc] = cover[rt] * (len >> 1);
		Max[lc] = max(-1, sum[lc]);
		Max[rc] = max(-1, sum[rc]);
		Min[lc] = min(1, sum[lc]);
		Min[rc] = min(1, sum[rc]);
		Xor[lc] = Xor[rc] = 0;
		cover[rt] = 0;
	}
	if (Xor[rt]) {
		fxor(lc);
		fxor(rc);
		sum[lc] = -sum[lc];
		sum[rc] = -sum[rc];
		int t = Max[lc];
		Max[lc] = -Min[lc];
		Min[lc] = -t;
		t = Max[rc];
		Max[rc] = -Min[rc];
		Min[rc] = -t;
		Xor[rt] = 0;
	}
}

void buildTree(int l, int r, int rt) {
	cover[rt] = Xor[rt] = 0;
	if (l == r) {
		if (str[l] == '(') sum[rt] = Max[rt] = Min[rt] = -1;
		else sum[rt] = Max[rt] = Min[rt] = 1;
		return;
	}
	int m = l + ((r - l) >> 1);
	buildTree(lson);
	buildTree(rson);
	pushUP(rt);
}

void update(char op, int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		if (op == '(') {
			cover[rt] = -1;
			Max[rt] = -1;
			Min[rt] = sum[rt] = -(r - l + 1);
			Xor[rt] = 0;
		} else if (op == ')') {
			cover[rt] = 1;
			Max[rt] = sum[rt] = r - l + 1;
			Min[rt] = 1;
			Xor[rt] = 0;
		} else if (op == 'r') {
			fxor(rt);
			sum[rt] = -sum[rt];
			int t = Max[rt];
			Max[rt] = -Min[rt];
			Min[rt] = -t;
		}
		return;
	}
	pushDown(rt, r - l + 1);
	int m = l + ((r - l) >> 1);
	if (L <= m) update(op, L, R, lson);
	if (R > m) update(op, L, R, rson);
	pushUP(rt);
}

int query1(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	pushDown(rt, r - l + 1);
	int m = l + ((r - l) >> 1);
	int ans = 0;
	if (L <= m) ans += query1(L, R, lson);
	if (R > m) ans += query1(L, R, rson);
	return ans;
}

int query2(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return Max[rt];
	}
	pushDown(rt, r - l + 1);
	int m = l + ((r - l) >> 1);
	int ans = 0;
	if (R <= m) ans = query2(L, R, lson);
	else if (L > m) ans = query2(L, R, rson);
	else ans = max(query2(L, R, lson), query1(L, R, lson) + query2(L, R, rson));
	return ans;
}

int main() {
	freopen("1546.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		printf("Case %d:\n", cas++);
		scanf("%d%s%d", &n, str, &q);
		buildTree(0, n - 1, 1);
		char op[8], ch[2];
		int a, b;
		for (int i = 0; i < q; i++) {
			scanf("%s", op);
			scanf("%d %d", &a, &b);
			if (op[0] == 's') {
				scanf("%s", ch);
				update(ch[0], a, b, 0, n - 1, 1);
			} else if (op[0] == 'r') {
				update('r', a, b, 0, n - 1, 1);
			} else {
				if ((a - b) & 1) {
					int o1 = query1(a, b, 0, n - 1, 1);
					int t2 = query2(a, b, 0, n - 1, 1);
					if (o1 == 0 && t2 <= 0) {
						printf("YES\n");
					} else printf("NO\n");
				} else {
					printf("NO\n");
				}
			}
		}
		printf("\n");
	}

	return 0;
}
