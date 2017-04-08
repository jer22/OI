#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

int n;
int root[MAXN], ls[MAXN * 80], rs[MAXN * 80], cnt = 0;
long long sum[MAXN * 80];

void insert(int x, int &y, int l, int r, long long val) {
	y = ++cnt;
	sum[y] = sum[x] + val;
	ls[y] = ls[x], rs[y] = rs[x];
	if (l == r) return;
	int mid = l + r >> 1;
	if (val <= mid) insert(ls[x], ls[y], l, mid, val);
	else insert(rs[x], rs[y], mid + 1, r, val);
}

long long query(int x, int y, int l, int r, int L, int R) {
	if (L <= l && r <= R) return sum[y] - sum[x];
	int mid = l + r >> 1;
	long long ans = 0;
	if (L <= mid) ans += query(ls[x], ls[y], l, mid, L, R);
	if (R > mid) ans += query(rs[x], rs[y], mid + 1, r, L, R);
	return ans;
}

int main() {
	freopen("4299.in", "r", stdin);
	scanf("%d", &n);
	long long x;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x);
		insert(root[i - 1], root[i], 1, INF, x);
	}
	int q;
	scanf("%d", &q);
	int l, r;
	while (q--) {
		scanf("%d %d", &l, &r);
		long long ans = query(root[l - 1], root[r], 1, INF, 1, 1);
		long long t;
		long long R;
		do {
			R = ans + 1;
			ans = query(root[l - 1], root[r], 1, INF, 1, R);
		} while (ans >= R && R < INF);
		printf("%lld\n", ans + 1);
	}


	return 0;
}
