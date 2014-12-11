#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

#define root 1, n, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 200010;

int T;
int n;
int add[MAXN];
int sum[MAXN];
void pushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void buildTree(int l, int r, int rt) {
	add[rt] = 0;
	if (l == r) {
		cin >> sum[rt];
		return;
	}
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(rt);
}

void update(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && R >= r) {
		sum[rt] += v;
		return;
	}
	int m = (r + l) >> 1;
	if (L <= m) update(L, R, v, lch);
	if (m < R) update(L, R, v, rch);
	pushUp(rt);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) return sum[rt];
	int m = (l + r) >> 1;
	int ans = 0;
	if (L <= m) ans += query(L, R, lch);
	if (m < R) ans += query(L, R, rch);
	return ans;
}

int main() {
	freopen("1166.in", "r", stdin);
	scanf("%d", &T);
	int t = 0;
	while (T--) {
		t++;
		printf("Case %d:\n", t);
		scanf("%d", &n);
		char str[10];
		int a, b;
		buildTree(root);
		while (~scanf("%s", str)) {
			if (str[0] == 'E') break;
			if (str[0] == 'A') {
				scanf("%d %d", &a, &b);
				update(a, a, b, root);
			} else if (str[0] == 'S') {
				scanf("%d %d", &a, &b);
				update(a, a, -b, root);
			} else {
				scanf("%d %d", &a, &b);
				printf("%d\n", query(a, b, root));
			}
		}
	}

	return 0;
}
