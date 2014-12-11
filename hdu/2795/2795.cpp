#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define root 1, n, 1
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 200000 << 2;

int h, w, n;
int x;
int tree[MAXN];
void pushUp(int rt) {
	tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}

void buildTree(int l, int r, int rt) {
	tree[rt] = w;
	if (l == r) return;
	int m = (l + r) >> 1;
	buildTree(lch);
	buildTree(rch);
}

int query(int x, int l, int r, int rt) {
	if (l == r) {
		tree[rt] -= x;
		return l;
	}
	int m = (l + r) >> 1;
	int ans = (tree[rt << 1] >= x) ? query(x, lch) : query(x, rch);
	pushUp(rt);
	return ans;
}

int main() {
	freopen("2795.in", "r", stdin);
	while (~scanf("%d %d %d", &h, &w, &n)) {
		if (h > n) h = n;
		buildTree(root);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			if (tree[1] < x) printf("-1\n");
			else {
				printf("%d\n", query(x, 1, h, 1));
			}
		}
	}


	return 0;
}
