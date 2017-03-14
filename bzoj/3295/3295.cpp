#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, q;
int arr[MAXN], pos[MAXN], sum[MAXN][2], c[MAXN];
int getsum(int *cc, int p) {
	int ans = 0;
	for (int i = p; i; i -= i & -i)
		ans += cc[i];
	return ans;
}

int root[MAXN], tot = 0, siz[5000005];
int tr[5000005][2];

void update(int &x, int l, int r, int p) {
	if (!x) x = ++tot;
	siz[x]++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (p <= mid) update(tr[x][0], l, mid, p);
	else update(tr[x][1], mid + 1, r, p);
}

int getup(int x, int l, int r, int num) {
	if (l == r) {
		return 0;
	}
	int mid = l + r >> 1;
	if (num <= mid) return siz[tr[x][1]] + getup(tr[x][0], l, mid, num);
	else return getup(tr[x][1], mid + 1, r, num);
}

int getdown(int x, int l, int r, int num) {
	if (l == r) {
		return 0;
	}
	int mid = l + r >> 1;
	if (num > mid) return siz[tr[x][0]] + getdown(tr[x][1], mid + 1, r, num);
	else return getdown(tr[x][0], l, mid, num);
}

int main() {
	freopen("3295.in", "r", stdin);
	scanf("%d %d", &n, &q);
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		pos[arr[i]] = i;
		sum[i][0] = getsum(c, n) - getsum(c, arr[i]);
		sum[i][1] = arr[i] + sum[i][0] - i;
		ans += (long long)sum[i][0];
		for (int j = arr[i]; j <= n; j += j & -j)
			c[j]++;
	}
	int x;
	for (int i = 1; i <= q; i++) {
		printf("%lld\n", ans);
		scanf("%d", &x);
		x = pos[x];

		ans -= sum[x][0] + sum[x][1];
		for (int j = x - 1; j; j -= j & -j)
			ans += getup(root[j], 1, n, arr[x]);
		for (int j = x; j; j -= j & -j)
			ans -= getdown(root[j], 1, n, arr[x]);
		for (int j = n; j; j -= j & -j)
			ans += getdown(root[j], 1, n, arr[x]);
		for (int j = x; j <= n; j += j & -j)
			update(root[j], 1, n, arr[x]);
	}


	return 0;
}
