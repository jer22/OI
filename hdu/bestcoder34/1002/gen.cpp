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
	freopen("hack", "w", stdout);
	srand(time(0));
	printf("50000 43345 50000\n");
	for (int i = 1; i <= 50000; i++) {
		if (i > 1) cout << ' ';
		int t = rand() % 5000 + 45000;
		cout << t;
	}
	

	return 0;
}
