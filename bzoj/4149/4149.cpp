#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

const int MAXN = 500005;

#define pii pair<int, int>
#define mp(i, j) make_pair(i, j)
#define lch rt << 1
#define rch rt << 1 | 1
#define mid (l + r >> 1)
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define INF 0x3f3f3f3f
#define solve(tt) {\
	sort(mi + 1, mi + n + 1);\
	sort(mx + 1, mx + n + 1);\
	memset(mxx, 0, sizeof(mxx));\
	for (int i = 1, id = 0; i <= n; i++) {\
		while (id < n && mx[id + 1].l <= mi[i].l) ++id, insert(mx[id].id, mx[id].r);\
		int rr = query(mi[i].l, mi[i].r);\
		if (rr < mi[i].id) continue;\
		int len = min(rr, mi[i].r) - mi[i].l + 1;\
		if (len > ans) {\
			ans = len;\
			ll = mi[i].l;\
		} else if (len == ans && mi[i].l < ll) ll = mi[i].l;\
	}\
}

struct Node{
	int l, r, id;
	Node() {}
	Node(int a, int b, int c) : l(a), r(b), id(c) {}
	bool operator < (const Node &n) const {
		return l < n.l;
	}
};
int n;
int arr[MAXN];
Node mi[MAXN], mx[MAXN];

int mxx[MAXN << 2];
void insert(int pos, int v, int l = 1, int r = n, int rt = 1) {
	if (l == r) {mxx[rt] = v; return;}
	if (pos <= mid) insert(pos, v, lson);
	else insert(pos, v, rson);
	mxx[rt] = max(mxx[lch], mxx[rch]);
}
int query(int L, int R, int l = 1, int r = n, int rt = 1) {
	if (L <= l && r <= R) return mxx[rt];
	int ans = -INF;
	if (L <= mid) ans = max(ans, query(L, R, lson));
	if (R > mid) ans = max(ans, query(L, R, rson));
	return ans;
}
bool cc(Node a, Node b) {return a.id < b.id;}

int lll[MAXN], rrr[MAXN], llll[MAXN], rrrr[MAXN];
int main() {
	freopen("4149.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		mi[i].id = mx[i].id = i;
	}
	int q[MAXN], t = 0;
	int i;
	for (q[t = 0] = 0, i = 1; i <= n; q[++t] = i++) {
		while (t && arr[q[t]] > arr[i]) --t;
		lll[i] = q[t] + 1;

	}
	for (q[t = 0] = n + 1, i = n; i >= 1; q[++t] = i--) {
		while (t && arr[q[t]] > arr[i]) --t;
		rrr[i] = q[t] - 1;
	}
	for (q[t = 0] = 0, i = 1; i <= n; q[++t] = i++) {
		while (t && arr[q[t]] < arr[i]) --t;
		llll[i] = q[t] + 1;
	}
	for (q[t = 0] = n + 1, i = n; i >= 1; q[++t] = i--) {
		while (t && arr[q[t]] < arr[i]) --t;
		rrrr[i] = q[t] - 1;
	}
	int ans = 0, ll = 0;
	for (int i = 1; i <= n; i++)
		mi[i] = Node(lll[i], rrr[i], i), mx[i] = Node(llll[i], rrrr[i], i);
	solve(0);
	for (int i = 1; i <= n; i++)
		mi[i] = Node(llll[i], rrrr[i], i), mx[i] = Node(lll[i], rrr[i], i);

	solve(1);
	printf("%d %d\n", ans, ll);

	return 0;
}
