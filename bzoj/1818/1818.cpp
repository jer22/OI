#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

struct Point{
	int x, y, pos;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		else return y < p.y;
	}
};

int n;
Point p[MAXN];
int t[MAXN << 1], tot = 0;
int lef[MAXN << 1], rig[MAXN << 1];

int get(int x) {
	return lower_bound(t + 1, t + tot + 1, x) - t;
}

int c[MAXN << 1];
int lowbit(int x) {
	return x & (-x);
}
void insert(int pos, int v) {
	for (int i = pos; i <= MAXN << 1; i += lowbit(i))
		c[i] += v;
}
int getsum(int pos) {
	int ans = 0;
	for (int i = pos; i; i -= lowbit(i))
		ans += c[i];
	return ans;
}

int main() {
	freopen("1818.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i].x, &p[i].y);
		t[++tot] = p[i].x;
		t[++tot] = p[i].y;
	}
	sort(t + 1, t + tot + 1);
	tot = unique(t + 1, t + tot + 1) - t - 1;

	memset(lef, 0x3f, sizeof(lef));

	for (int i = 1; i <= n; i++) {
		p[i].x = get(p[i].x), p[i].y = get(p[i].y);

		lef[p[i].y] = min(lef[p[i].y], p[i].x);
		rig[p[i].y] = max(rig[p[i].y], p[i].x);
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++) {
		if (lef[p[i].y] == rig[p[i].y]) p[i].pos = 0;
		else if (lef[p[i].y] == p[i].x) p[i].pos = 1;
		else if (rig[p[i].y] == p[i].x) p[i].pos = -1;
		else p[i].pos = 0;
	}
	int ans = n;
	for (int i = 1; i <= n; ) {
		int rr = i;
		while (rr < n && p[i].x == p[rr + 1].x) rr++;
		// cout << i << ' ' << rr << endl;
		for (int j = i; j <= rr; j++) {
			if (p[j].pos == -1) insert(p[j].y, -1);
		}
		ans += max(0, getsum(p[rr].y - 1) - getsum(p[i].y));
		for (; i <= rr; i++) {
			if (p[i].pos == 1) insert(p[i].y, 1);
		}
	}
	printf("%d\n", ans);

	return 0;
}
