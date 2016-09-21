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
	freopen("1818.inin", "w", stdout);
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
	}
	cout << n << endl;
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++) {
		cout << p[i].x << ' ' << p[i].y << endl;
	}


	return 0;
}
