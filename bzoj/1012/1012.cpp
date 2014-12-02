#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 200010

using namespace std;

int m, mod;
int ans;
int len;

struct Tnode {
	int lc, rc, max;
}tree[MAXN << 2];

void build(int root, int l, int r) {
	int mid = l + r >> 1;
	tree[root].lc = l;
	tree[root].rc = r;
	if (l == r) {
		return;
	}
	build(root << 1, l, mid);
	build((root << 1) + 1, mid + 1, r);
}

void insert(int root, int l, int r, int value) {
	if (tree[root].lc == l && tree[root].rc == r) {
		tree[root].max = value;
		return;
	}
	if (tree[root].lc == tree[root].rc) {
		return;
	}
	int mid = tree[root].lc + tree[root].rc >> 1;
	if (mid >= r) {
		insert(root << 1, l, r, value);
	} else if (mid < l) {
		insert((root << 1) + 1, l, r, value);
	} else {
		insert(root << 1, l, mid, value);
		insert((root << 1) + 1, mid + 1, r, value);
	}
	tree[root].max = max(tree[root << 1].max, tree[(root << 1) + 1].max);
}

int find(int root, int l, int r) {
	if (tree[root].lc == l && tree[root].rc == r) {
		return tree[root].max;
	}
	int mid = tree[root].lc + tree[root].rc >> 1;
	if (mid >= r) {
		return find(root << 1, l, r);
	} else if (mid < l) {
		return find((root << 1) + 1, l, r);
	} else {
		return max(find(root << 1, l, mid), find((root << 1) + 1, mid + 1, r));
	}
}

int main( void ) {
	scanf("%d %d", &m, &mod);
	build(1, 1, m);
	char c[3];
	int x;
	for (int i = 0; i < m; i++) {
		scanf("%s %d", &c, &x);
		if (c[0] == 'A') {
			len++;
			insert(1, len, len, (ans + x) % mod);
		} else if (c[0] == 'Q') {
			ans = find(1, len - x + 1, len);
			printf("%d\n", ans);
		}
	}

	return 0;
}
