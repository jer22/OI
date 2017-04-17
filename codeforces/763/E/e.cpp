#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define MAXN 100005
#define ROOT int l = 1, int r = n, int rt = 1
#define lch rt << 1
#define rch rt << 1 | 1
#define mid (l + r >> 1)
#define lson l, mid, lch
#define rson mid + 1, r, rch

int n, m;
vector<int> lef[MAXN], rig[MAXN];
int num[MAXN << 2];
// int fro[MAXN << 2][6], rea[MAXN << 2][6];

int findfa(int p, int *fa) {
	return (p == fa[p]) ? p : fa[p] = findfa(fa[p], fa);
}

int un(int a, int b, int *fa) {
	a = findfa(a, fa), b = findfa(b, fa);
	fa[a] = b;
	if (a == b) return 0;
	return 1;
}

void build(ROOT) {
	if (l == r) {
		num[rt] = 1;
		return;
	}
	build(lson), build(rson);
	num[rt] = num[lch] + num[rch];
	int fa[13];
	for (int i = 1; i <= 12; ++i)
		fa[i] = i;
	for (int i = max(mid - 5, l); i <= mid; ++i)
		for (auto nex : rig[i]) if (nex <= mid)
			un(6 - mid + i, nex - mid + 6, fa);
	for (int i = mid + 1; i <= min(r, mid + 6); ++i)
		for (auto nex : rig[i]) if (nex <= min(r, mid + 6))
			un(6 - mid + i, nex - mid + 6, fa);
	for (int i = max(mid - 5, l); i <= mid; ++i) {
		for (auto nex : rig[i]) if (nex > mid && nex <= min(r, mid + 6)) {
			// if (l == 1 && r == 7) cout << i << ' ' << nex << endl;
			num[rt] -= un(6 - mid + i, nex - mid + 6, fa);
		}
	}

}

int query(int L, int R, ROOT) {
	if (L <= l && r <= R) return num[rt];
	if (L > mid) return query(L, R, rson);
	if (R <= mid) return query(L, R, lson);
	int ans = query(L, R, lson) + query(L, R, rson);
	int fa[13];
	for (int i = 1; i <= 12; ++i)
		fa[i] = i;

	for (int i = max(max(L, l), mid - 5); i <= mid; ++i)
		for (auto nex : rig[i]) if (nex <= mid)
			un(6 - mid + i, nex - mid + 6, fa);
	for (int i = mid + 1; i <= min(R, min(r, mid + 6)); ++i)
		for (auto nex : rig[i]) if (nex <= min(mid + 6, min(r, R)))
			un(6 - mid + i, nex - mid + 6, fa);

	for (int i = max(max(L, l), mid - 5); i <= mid; ++i)
		for (auto nex : rig[i]) if (nex > mid && nex <= min(mid + 6, min(r, R))) {
			ans -= un(6 - mid + i, nex - mid + 6, fa);
		}
	return ans;
}

int main() {
	freopen("e.in", "r", stdin);
	int k;
	scanf("%d %d", &n, &k);
	scanf("%d", &m);
	for (int i = 0, a, b; i < m; ++i) {
		scanf("%d %d", &a, &b);
		if (a > b) swap(a, b);
		rig[a].push_back(b);
		lef[b].push_back(a);
	}
	build();
	int q;
	scanf("%d", &q);
	int a, b;
	while (q--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", query(a, b));
	}

	return 0;
}
