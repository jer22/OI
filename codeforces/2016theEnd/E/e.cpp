#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 200005;

struct Node{
	int a[6][6];
	Node() {
		memset(a, 0x3f, sizeof(a));
	}
};

int n, q;
Node dp[MAXN << 2];
char str[MAXN];

Node merge(Node a, Node b) {
	Node c;
	for (int i = 0; i < 5; i++)
		for (int j = i; j < 5; j++)
			for (int k = j; k < 5; k++)
				c.a[i][k] = min(c.a[i][k], a.a[i][j] + b.a[j][k]);
	return c;
}

void build(int l, int r, int rt) {
	if (l == r) {
		for (int i = 0; i < 5; i++)
			dp[rt].a[i][i] = 0;
		if (str[l] == '2')
			dp[rt].a[0][0] = 1, dp[rt].a[0][1] = 0;
		else if (str[l] == '0')
			dp[rt].a[1][1] = 1, dp[rt].a[1][2] = 0;
		else if (str[l] == '1')
			dp[rt].a[2][2] = 1, dp[rt].a[2][3] = 0;
		else if (str[l] == '7')
			dp[rt].a[3][3] = 1, dp[rt].a[3][4] = 0;
		else if (str[l] == '6')
			dp[rt].a[3][3] = 1, dp[rt].a[4][4] = 1;
		return;
	}
	int m = l + r >> 1;
	build(lson);
	build(rson);
	dp[rt] = merge(dp[lch], dp[rch]);
}

Node query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) return dp[rt];
	int m = l + r >> 1;
	if (m >= R) return query(L, R, lson);
	if (m < L) return query(L, R, rson);
	return merge(query(L, R, lson), query(L, R, rson));
}

int main() {
	// freopen("e.in", "r", stdin);
	scanf("%d %d", &n, &q);
	scanf("%s", str + 1);
	build(1, n, 1);
	for (int i = 0, l, r; i < q; i++) {
		scanf("%d %d", &l, &r);
		Node ans = query(l, r, 1, n, 1);
		if (ans.a[0][4] == 0x3f3f3f3f) ans.a[0][4] = -1;
		printf("%d\n", ans.a[0][4]);
	}

	return 0;
}
