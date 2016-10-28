#include <bits/stdc++.h>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, m, lch
#define rson m + 1, r, rch

using namespace std;

const int MAXN = 100005;
const int MAXM = 2000005;

struct Point{
	int x, y, val;
	Point() {}
	Point(int a, int b, int c) : x(a), y(b), val(c) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

int n, K;
Point p[MAXN];
int val[MAXM << 2], mx[MAXM << 2];

void pushdown(int rt) {
	if (val[rt]) {
		val[lch] += val[rt];
		val[rch] += val[rt];
		mx[lch] += val[rt];
		mx[rch] += val[rt];
		val[rt] = 0;
	}
}
void pushup(int rt) {
	mx[rt] = max(mx[lch], mx[rch]);
}

void insert(int L, int R, int v, int l, int r, int rt) {
	if (L <= l && r <= R) {
		val[rt] += v;
		mx[rt] += v;
		return;
	}
	pushdown(rt);
	int m = l + r >> 1;
	// cout << L << ' ' << R << ' ' << l << ' ' << r << ' ' << m << endl;
	if (L <= m) insert(L, R, v, lson);
	if (R > m) insert(L, R, v, rson);
	pushup(rt);
}

int main() {
	freopen("3476.in", "r", stdin);
	scanf("%d %d", &n, &K);
	int a, b, c;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &c, &a, &b);
		p[i] = Point(a + b, a - b + 1000001, c);
	}
	sort(p + 1, p + n + 1);
	int l = 1, r = 1;
	int ans = 0;

	for (int i = 1; i <= n; i++) {
		insert(p[i].y - K, p[i].y + K, p[i].val, 1, 2000001, 1);
		while (l < i && p[i].x - p[l].x > K * 2) {
			insert(p[l].y - K, p[l].y + K, -p[l].val, 1, 2000001, 1);
			l++;
		}

		// int sum = getans(p[i].y + K) - getans(p[i].y - K - 1);
		ans = max(ans, mx[1]);
	}
	printf("%d\n", ans);

	return 0;
}
