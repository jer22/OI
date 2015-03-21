#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cmath>

#define MAXN 100005
#define INF 0x7fffffff

using namespace std;

const double eps = 1e-8;

struct Point{
	double x, y;
	Point() {}
	Point(double a, double b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int n;
Point p[MAXN];
Point temp[MAXN];

bool cmp(Point a, Point b) { return a.y < b.y; }

double dist(int a, int b) {
	double t = (p[a].x - p[b].x) * (p[a].x - p[b].x) + (p[a].y - p[b].y) * (p[a].y - p[b].y);
	return t;
}

double dist(Point a, Point b) {
	double t = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return t;
}

double dfs(int l, int r) {
	int mid = l + r >> 1;
	if (l + 1 == r) return dist(l, r);
	if (l + 2 == r) return min(dist(l, r), min(dist(l, l + 1), dist(l + 1, r)));
	double best = min(dfs(l, mid), dfs(mid + 1, r));
	int tot = 0;
	for (int i = l; i <= r; i++)
		if (p[i].x >= p[mid].x - best && p[i].x <= p[mid].x + best)
			temp[tot++] = p[i];
	sort(temp, temp + tot, cmp);
	for (int i = 0; i < tot; i++)
		for (int j = i + 1; j < tot; j++)
			if (temp[j].y - temp[i].y >= best) break;
			else best = min(best, dist(temp[i], temp[j]));
	return best;
}

int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		sort(p, p + n);
		double ans = sqrt(dfs(0, n - 1)) / 2;
		printf("%.2lf\n", ans);
	}
	return 0;
}
