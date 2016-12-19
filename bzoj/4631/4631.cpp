#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch
#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))
#define fi first
#define se second
#define pushup(rt) (mx[rt] = max(mx[lch], mx[rch]))

using namespace std;

const int MAXN = 100005;

int n, m;
int arr[MAXN], mx[MAXN << 2];
pii kid[MAXN];
vector<int> edges[MAXN << 2];
int num[MAXN];
int ans = 0;

void build(int l, int r, int rt) {
	if (l == r) {
		mx[rt] = bool(arr[l]);
		return;
	}
	int mid = l + r >> 1;
	build(lson);
	build(rson);
	pushup(rt);
}

void addEdge(int i, int l, int r, int rt) {
	int L = kid[i].fi, R = kid[i].se;
	if (L <= l && r <= R) {
		edges[rt].push_back(i);
		num[i]++;
		return;
	}
	int mid = l + r >> 1;
	if (L <= mid) addEdge(i, lson);
	if (mid < R) addEdge(i, rson);
}

void modify(int rt) {
	for (int i = 0; i < edges[rt].size(); i++) {
		int j = edges[rt][i];
		num[j]--;
		if (!num[j]) ans++;
	}
}

void update(int pos, int l, int r, int rt) {
	if (pos == l && pos == r) {
		mx[rt] = 0;
		modify(rt);
		return;
	}
	int mid = l + r >> 1;
	if (pos <= mid) update(pos, lson);
	else update(pos, rson);
	pushup(rt);
	if (!mx[rt]) modify(rt);
}

int main() {
	freopen("4631.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	build(1, n, 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &kid[i].fi, &kid[i].se);
		addEdge(i, 1, n, 1);
	}
	int q;
	scanf("%d", &q);
	int lastans = 0, x;
	// update(2, 1, n, 1);
	// update(1, 1, n, 1);
	// update(3, 1, n, 1);
	while (q--) {
		scanf("%d", &x);
		x = (x + lastans - 1) % n + 1;
		// cout << x << endl;
		arr[x]--;
		if (!arr[x]) {
			update(x, 1, n, 1);
		}
		lastans = ans;
		printf("%d\n", ans);
	}

	return 0;
}
