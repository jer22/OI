#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define root 1, n, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 200000 << 2;

int n, m;
int arr[MAXN];

void pushUp(int rt) {
	arr[rt] = max(arr[rt << 1], arr[rt << 1 | 1]);
}

void buildTree(int l, int r, int rt) {
	if (l == r) {
		scanf("%d", &arr[rt]);
		return;
	}
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
	pushUp(rt);
}

void update(int a, int v, int l, int r, int rt) {
	if (l == r) {
		arr[rt] = v;
		return;
	}
	int m = (l + r) >> 1;
	if (m >= a) update(a, v, lch);
	if (m < a) update(a, v, rch);
	pushUp(rt);
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return arr[rt];
	}
	int m = (l + r) >> 1;
	int ans = 0;
	if (m >= L) ans = max(ans, query(L, R, lch));
	if (m < R) ans = max(ans, query(L, R, rch));
	return ans;
}

int main() {
	freopen("1754.in", "r", stdin);
	while (~scanf("%d%d", &n, &m)) {
		char ch[2];
		int a, b;
		buildTree(root);
		while (m--) {
			scanf("%s", ch);
			scanf("%d %d", &a, &b);
			if (ch[0] == 'U') {
				update(a, b, root);
			} else {
				printf("%d\n", query(a, b, root));
			}
		}
	}

	return 0;
}
