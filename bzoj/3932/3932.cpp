#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Node{
	int pos, c, f;
	bool operator < (const Node &n) const {
		return pos < n.pos;
	}
};

long long t[MAXN], cnt = 0;
int gethash(int x) {
	return lower_bound(t + 1, t + cnt + 1, x) - t;
}

int n, q;
int root[MAXN], ls[5000005], rs[5000005], siz[5000005], tot = 0;
long long sum[5000005];

Node arr[MAXN << 1];

void insert(int x, int &y, int l, int r, int v, int f) {
	y = ++tot;
	siz[y] = siz[x] + f;
	sum[y] = sum[x] + f * t[v];
	if (l == r) return;
	ls[y] = ls[x], rs[y] = rs[x];
	int m = l + r >> 1;
	if (v <= m) insert(ls[x], ls[y], l, m, v, f);
	else insert(rs[x], rs[y], m + 1, r, v, f);
}

long long query(int x, int l, int r, int k) {
	if (l == r) return (long long)t[l] * min(k, siz[x]);
	int mid = l + r >> 1;
	if (k <= siz[ls[x]]) return query(ls[x], l, mid, k);
	return query(rs[x], mid + 1, r, k - siz[ls[x]]) + sum[ls[x]];
}

int main() {
	freopen("3932.in", "r", stdin);
	scanf("%d %d", &n, &q);
	long long pre = 1ll;
	int a, b, c;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		t[i] = c;
		arr[(i << 1) - 1] = (Node){a, c, 1};
		arr[i << 1] = (Node){b + 1, c, -1};
	}
	sort(t + 1, t + n + 1);
	cnt = unique(t + 1, t + n + 1) - t - 1;
	sort(arr + 1, arr + (n << 1) + 1);
	for (int i = 1, j = 1; i <= q; i++) {
		root[i] = root[i - 1];
		for (; j <= n << 1 && arr[j].pos == i; j++) {
			insert(root[i], root[i], 1, cnt, gethash(arr[j].c), arr[j].f);
		}
	}
	int xx;
	long long ai, bi, ci;
	for (int i = 1; i <= q; i++) {
		scanf("%d %lld %lld %lld", &xx, &ai, &bi, &ci);
		long long ki = 1 + ((ai * pre % ci) + bi) % ci;
		long long ans = query(root[xx], 1, cnt, ki);
		printf("%lld\n", ans);
		pre = ans;
	}


	return 0;
}
