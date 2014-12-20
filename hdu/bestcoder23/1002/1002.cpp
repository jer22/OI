#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1

using namespace std;

const int MAXN = 50011;

int T;
int n;
int arr[MAXN];
long long c[MAXN];
int sum[MAXN << 2];
long long brr[MAXN];
long long crr[MAXN];

int lowbit(int x) {
	return x & (-x);
}
void pushUp(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

int query(int L, int R, int l, int r, int rt) {
	if (L <= l && R >= r) {
		return sum[rt];
	}
	int m = l + r >> 1;
	int ans = 0;
	if (L <= m) ans += query(L, R, lch);
	if (R > m) ans += query(L, R, rch);
	return ans;
}

void update(int p, int l, int r, int rt) {
	if (l == r) {
		sum[rt] = 1;
		return;
	}
	int m = l + r >> 1;
	if (p <= m) update(p, lch);
	else update(p, rch);
	pushUp(rt);
}

void insert(int x) {
	for (int i=x;i<=n;i+=lowbit(i))
		c[i]++;
}

long long getAns(int x) {
	long long sum=0;
	for (int i=x;i>0;i-=lowbit(i))
		sum+=c[i];
	return sum;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(c, 0, sizeof(c));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			brr[i] = getAns(arr[i]);
			brr[i] += brr[i - 1];
			insert(arr[i]);
		}
		memset(c, 0, sizeof(c));
		long long ans = 0;
		for (int i = n; i >= 1; i--) {
			crr[i] = getAns(n - arr[i] + 1);
			// cout << crr[i] << ' ';
			ans += crr[i] * brr[i - 1];
			insert(n - arr[i] + 1);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
