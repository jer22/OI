#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

#define lef rt << 1
#define rig rt << 1 | 1
#define lch l, m, lef
#define rch m + 1, r, rig
#define roo 1, n, 1
#define this l, r, rt

using namespace std;

const int MAXN = 50002;

int n, q;
stack<int> des;
// bool mark[MAXN];
int lsum[MAXN << 2], rsum[MAXN << 2];

void pushUp(int l, int r, int rt) {
	int m = l + r >> 1;
	lsum[rt] = lsum[lef] + (lsum[lef] == m - l + 1 ? lsum[rig] : 0);
	rsum[rt] = rsum[rig] + (rsum[rig] == r - m ? rsum[lef] : 0);
}

void buildTree(int l, int r, int rt) {
	lsum[rt] = rsum[rt] = r - l + 1;
	if (l == r) return;
	int m = l + r >> 1;
	buildTree(lch);
	buildTree(rch);
}

void update(int w, int p, int l, int r, int rt) {
	if (l == r) {
		lsum[rt] = rsum[rt] = w;
		return;
	}
	int m = l + r >> 1;
	if (p <= m) update(w, p, lch);
	else update(w, p, rch);
	pushUp(this);
}

int query(int p, int l, int r, int rt) {
	if (l == r) {
		return lsum[rt];
	}
	int m = l + r >> 1;
	if (p <= m) {
		if (p >= m - rsum[lef] + 1) return rsum[lef] + lsum[rig];
		else return query(p, lch);
	} else {
		if (p <= lsum[rig] + m) return rsum[lef] + lsum[rig];
		else return query(p, rch);
	}
}

void solve() {
	// memset(mark, false, sizeof(mark));
	char op[2];
	int a;
	for (int i = 0; i < q; i++) {
		scanf("%s", op);
		if (op[0] == 'D') {
			scanf("%d", &a);
			// mark[a] = 1;
			des.push(a);
			update(0, a, roo);
		} else if (op[0] == 'R') {
			if (des.size()) {
				update(1, des.top(), roo);
				des.pop();
			}
		} else {
			scanf("%d", &a);
			printf("%d\n", query(a, roo));
		}
	}
}

int main() {
	freopen("1540.in", "r", stdin);
	while (~scanf("%d %d", &n, &q)) {
		buildTree(roo);
		solve();
	}


	return 0;
}
