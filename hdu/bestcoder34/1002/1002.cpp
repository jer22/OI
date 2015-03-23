#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <map>

#define INF 0x3f3f3f3f
#define lch rt << 1
#define rch rt<< 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 150005;

int n, W, H;
long long val[MAXN << 2];
long long away[MAXN << 2], come[MAXN << 2];

void pushup(int rt) {
	away[rt] = away[lch] + away[rch];
	come[rt] = come[lch] + come[rch];
}

void build(int l, int r, int rt) {
	int mid = l + r >> 1;
	if (l == r) {
		if (val[l] - H >= 0) {
			away[rt] = val[l] - H;
			come[rt] = 0;
		} else {
			come[rt] = H - val[l];
			away[rt] = 0;
		}
		return;
	}
	build(lson);
	build(rson);
	pushup(rt);
}

long long q_come(int l, int r, int rt, int L, int R) {
	if (L <= l && R >= r) {
		return come[rt];
	}
	int mid = l + r >> 1;
	long long ans = 0;
	if (L <= mid) ans += q_come(lson, L, R);
	if (R > mid) ans += q_come(rson, L, R);
	return ans;
}

long long q_away(int l, int r, int rt, int L, int R) {
	if (L <= l && R >= r) {
		return away[rt];
	}
	int mid = l + r >> 1;
	int ans = 0;
	if (L <= mid) ans += q_away(lson, L, R);
	if (R > mid) ans += q_away(rson, L, R);
	return ans;
}

int main() {
	freopen("1002.in", "r", stdin);
	while (~scanf("%d %d %d", &n, &W, &H)) {	
		memset(val, 0, sizeof(val));
		long long sum = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lld", &val[i + n]);
			sum += val[i + n];
		}
		if (sum < W * H) {
			cout << -1 << endl;
			continue;
		}
		n *= 3;
		build(1, n, 1);
		int tot = n / 3;
		// cout << q_come(1, n, 1, 5, 8);
		// cout << come[1] << endl;
		long long res = INF;
		for (int i = 1; i <= tot * 2; i++) {
			long long x = q_come(1, n, 1, i, i + W - 1);
			long long y = q_away(1, n, 1, i, i + W - 1);
			// cout << x << ' ' << y << endl;
			long long t = min(x, y);
			long long ans = t;
			// cout << i << ' ' << x << ' ' << y << endl;
			x -= t;
			y -= t;
			ans += x;
			ans += y;
			// cout << ans << endl;
			res = min(res, ans);
		}
		cout << res << endl;
	}
	

	return 0;
}
