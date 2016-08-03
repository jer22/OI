#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <cmath>

using namespace std;

const int MAXN = 100005;

int n, q;
int arr[MAXN];
int cnt[MAXN][20], lef[MAXN], rig[MAXN];
int maxx[MAXN][20], tot;

void init() {
	for (int j = 1; j <= 17; j++)
		for (int i = 1; i <= tot; i++)
			if (i + (1 << j) - 1 <= tot)
				cnt[i][j] = max(cnt[i][j - 1], cnt[i + (1 << j - 1)][j - 1]);
}

int query(int l, int r) {
	int k = log(r - l + 1) / log(2);
	return max(cnt[l][k], cnt[r - (1 << k) + 1][k]);
}

int find(int x) {
	int l = 1, r = tot;
	while (lef[l] < lef[r]) {
		int m = (l + r >> 1) + 1;
		if (lef[m] <= x) l = m;
		else r = m - 1;
	}
	return l;
}

int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d", &n)) {
		if (!n) break;
		scanf("%d", &q);
		int t = 0, p = -146789821;
		memset(cnt, 0, sizeof(cnt));
		tot = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &t);
			if (t == p) arr[i] = arr[i - 1];
			else {
				tot++;
				arr[i] = arr[i - 1] + 1;
				lef[arr[i]] = i;
				rig[arr[i - 1]] = i - 1;
			}
			cnt[arr[i]][0]++;
			p = t;
		}
		rig[arr[n]] = n;
		int a, b;
		init();
		// cout << find(2) << endl;
		while (q--) {
			scanf("%d %d", &a, &b);
			int l = find(a);
			int r = find(b);
			if (l == r) {
				printf("%d\n", b - a + 1);
				continue;
			}
			int ans = 0;

			ans = max(b - lef[r] + 1, rig[l] - a + 1);
			if (r - l > 1) ans = max(ans, query(l + 1, r - 1));
			printf("%d\n", ans);
		}
	}

	return 0;
}
