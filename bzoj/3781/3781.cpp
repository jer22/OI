#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 50005;

struct Node{
	int l, r, id, block;
	bool operator < (const Node &n) const {
		if (block != n.block) return block < n.block;
		return r < n.r;
	}
};

int n, m, k;
int b[MAXN];
Node arr[MAXN];
long long res[MAXN];
int s[MAXN];

void solve() {
	sort(arr, arr + m);
	int l = 1, r = 0;
	long long  ans = 0;
	for (int i = 0; i < m; i++) {
		while (l > arr[i].l) l--, s[b[l]]++, ans += 2 * s[b[l]] - 1;
		while (r < arr[i].r) r++, s[b[r]]++, ans += 2 * s[b[r]] - 1;
		while (l < arr[i].l) s[b[l]]--, ans -= 2 * s[b[l]] + 1, l++;
		while (r > arr[i].r) s[b[r]]--, ans -= 2 * s[b[r]] + 1, r--;
		res[arr[i].id] = ans;
	}
}

int main() {
	freopen("3781.in", "r", stdin);
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &b[i]);
	int siz = sqrt(n);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &arr[i].l, &arr[i].r);
		arr[i].id = i;
		arr[i].block = (arr[i].l - 1) / siz + 1;
	}
	solve();
	for (int i = 0; i < m; i++)
		printf("%lld\n", res[i]);

	return 0;
}
