#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

const int MAXN = 10005;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y < p.y;
	}
};

int n;
Point p[MAXN];
set<Point> ans;
map<int, int> vis;
int has[MAXN];
set<int> verti[MAXN];

void solve(int l, int r) {
	if (l >= r) return;
	int m = l + r >> 1;
	int a = m, b = m;
	while (a > l && p[a - 1].x == p[m].x) a--;
	while (b < r && p[b].x == p[m].x) b++;
	for (int i = l; i < r; i++)
		ans.insert(Point(p[m].x, p[i].y ));

	solve(l, a);
	solve(b, r);

}

int main() {
	freopen("e.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	int totx = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &p[i].x, &p[i].y);
		// if (!vis[p[i].x]) {
		// 	vis[p[i].x] = ++totx;
		// 	has[totx] = p[i].x;
		// 	verti[totx].insert(p[i].y);
		// } else {
		// 	verti[vis[p[i].x]].insert(p[i].y);
		// }
		ans.insert(p[i]);
	}
	sort(p + 1, p + n + 1);
	solve(1, n + 1);
	int s = ans.size();
	printf("%d\n", s);
	for (set<Point>::iterator it = ans.begin(); it != ans.end(); it++) {
		printf("%d %d\n", it -> x, it -> y);
	}

	return 0;
}
