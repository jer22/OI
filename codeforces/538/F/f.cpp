#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;
const int INF = 0x3f3f3f3f;

int n;
int arr[MAXN];
int root[MAXN], ls[8000005], rs[8000005], siz[8000005], cnt = 0;

void insert(int x, int &y, int l, int r, int p) {
	y = ++cnt;
	siz[y] = siz[x] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	ls[y] = ls[x], rs[y] = rs[x];
	if (p <= mid) insert(ls[x], ls[y], l, mid, p);
	else insert(rs[x], rs[y], mid + 1, r, p);
}

int query(int a, int b, int l, int r, int x) {
	if (l == r) {
		if (l < x) return siz[a] - siz[b];
		return 0;
	}
	int mid = l + r >> 1;
	if (x <= mid) return query(ls[a], ls[b], l, mid, x);
	else return siz[ls[a]] - siz[ls[b]] + query(rs[a], rs[b], mid + 1, r, x);
}

int main() {
	freopen("f.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		insert(root[i - 1], root[i], -INF, INF, arr[i]);
	}
	for (int k = 1; k < n; k++) {
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int a = k * (i - 1) + 2, b = min(n, k * i + 1);
			if (a > n) break;
			ans += query(root[b], root[a - 1], -INF, INF, arr[i]);
		}
		cout << ans << endl;
	}



	return 0;
}
