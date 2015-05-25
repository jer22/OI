#include <bits/stdc++.h>

#define lowbit(x) ((x) & (-(x)))
#define MAXN 2005
#define MAXM 4005

using namespace std;

int q, n, m, len;
int s[2][MAXN][MAXM];
int x[1000005], y[1000005];

void add(int p, int x, int y, int v) {
	for (++x, ++y; x < MAXN; x += lowbit(x))
		for (int i = y; i < MAXM; i += lowbit(i))
			s[p][x][i] += v;
}

int sum(int p, int x, int y) {
	if (x < 0 || y < 0) return 0;
	int k = 0;
	if (++x > n) x = n + 1;
	if (++y > m) y = m + 1;
	for (; x; x -= lowbit(x))
		for (int i = y; i; i -= lowbit(i))
			k += s[p][x][i];
	return k;
}

void update(int t, int c, int l, int r, int d) {
	x[c] = (t - l * d + n) % n;
	y[c] = r - l;
	add(0, x[c], y[c] + x[c], 1);
	add(1, x[c], y[c] - x[c] + n, 1);
}

void del(int c) {
	add(0, x[c], y[c] + x[c], -1);
	add(1, x[c], y[c] - x[c] + n, -1);
}

int area(int p, int x1, int y1, int x2, int y2) {
	return sum(p, x2, y2) + sum(p, x1 - 1, y1 - 1) - sum(p, x1 - 1, y2) - sum(p, x2, y1 - 1);
}

int ask(int t, int l, int r) {
	int d = r == len;
	return area(0, t, l + t, t + r, m) + area(0, 0, l + t - n, t + r - n - d, m)
		+ area(1, n - r + t + d, l - t, n, m) + area(1, t - r, l - t + n, t - 1, m);
}

int main() {
	freopen("1062.in", "r", stdin);
	scanf("%d %d", &q, &len);
	n = len << 1;
	m = n << 1;
	int op, t;
	int a, b, c, d;
	while (q--) {
		scanf("%d %d", &op, &t);
		if (op == 1) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			update(t, a, b, c, d);
		} else if (op == 2) {
			scanf("%d %d", &a, &b);
			printf("%d\n", ask(t % n, a, b));
		} else {
			scanf("%d", &c);
			del(c);
		}
	}


	return 0;
}
