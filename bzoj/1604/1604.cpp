#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n, c;

struct Point{
	int x, y, id;
	Point() {}
	Point(int a, int b, int c) : x(a), y(b), id(c) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int ans;
Point p[MAXN];
int fa[MAXN], cnt[MAXN];
multiset<pair<int, int> > s;

int find(int p) {
	if (p == fa[p]) return p;
	return fa[p] = find(fa[p]);
}

void un(int a, int b) {
	int x = find(a), y = find(b);
	if (x != y) ans--;
	fa[x] = y;
}

int main() {
	freopen("1604.in", "r", stdin);
	scanf("%d %d", &n, &c);
	int a, b;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &a, &b);
		p[i] = Point(a + b, a - b, i);
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		fa[i] = i;
	ans = n;
	int l = 1;
	s.insert(make_pair(p[1].y, p[1].id));
	for (int i = 2; i <= n; i++) {
		// cout << p[i].x << ' ' << p[i].y << endl;
		while (l < i && p[i].x - p[l].x > c) {
			s.erase(s.find(make_pair(p[l].y, p[l].id)));
			l++;
		}
		set<pair<int, int> >::iterator it = s.lower_bound(make_pair(p[i].y, p[i].id));
		if (it != s.end() && it -> first - p[i].y <= c) un(p[i].id, it -> second);
		if (it != s.begin() && p[i].y - (--it) -> first <= c) un(p[i].id, it -> second);
		s.insert(make_pair(p[i].y, p[i].id));
	}
	int ma = 0;
	for (int i = 1; i <= n; i++) {
		cnt[find(i)]++;
		ma = max(ma, cnt[find(i)]);
	}
	printf("%d %d\n", ans, ma);

	return 0;
}
