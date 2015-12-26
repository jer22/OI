#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l , m , lch
#define rson m + 1 , r , rch

using namespace std;

const int MAXN = 50005;

int T;
int n;
int arr[MAXN], ans[MAXN];
int sum[MAXN << 2];

void pushUp(int rt) {
	sum[rt] = sum[lch] + sum[rch];
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && r <= R) {
		return sum[rt];
	}
	int m = l + r >> 1;
	int res = 0;
	if (L <= m) res += query(L, R, lson);
	if (R > m) res += query(L, R, rson);
	return res;
}

void update(int p, int l, int r, int rt) {
	if (l == p && r == p) {
		sum[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	if (p <= m) update(p, lson);
	else update(p, rson);
	pushUp(rt);
}

int main() {
	freopen("c.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		for (int i = n; i >= 1; i--)
			arr[i] -= arr[i - 1];
		memset(sum, 0, sizeof(sum));
		for (int i = n; i >= 1; i--) {
			int cur = arr[i];
			int ll = 1, rr = n;
			while (ll < rr) {
				int mm = (ll + rr >> 1) + 1;
				int tmp = query(mm, n, 1, n, 1);
				// if (i == 3) cout << query(1, 5, 1, n, 1) << endl;
				if (n - mm + 1 - tmp > cur) ll = mm;
				else  rr = mm - 1;
			}
			// ll--;
			update(ll, 1, n, 1);
			ans[i] = ll;
		}
		for (int i = 1; i <= n; i++) {
			if (i > 1) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");

	}


	return 0;
}
