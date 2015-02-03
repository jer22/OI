#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct Point{
	double x, y;
	Point() {}
	Point(double a, double b) : x(a), y(b) {}
	double len() {return sqrt(x * x + y * y);}
};

struct Polygon{
	Point p[35];
	int cnt;
};

struct Line{
	Point a, b;
	Line() {}
	Line(Point x, Point y) : a(x), b(y) {}
};

struct Vertical{
	Point p;
	double d;
	Vertical() {}
	Vertical(Point a, double b) : p(a), d(b) {}
};

const double eps = 1e-10;
int sign(double a) {return a > eps ? 1 : a < -eps ? -1 : 0;}

Point operator + (Point a, Point b) {return Point(a.x + b.x, a.y + b.y);}
Point operator - (Point a, Point b) {return Point(a.x - b.x, a.y - b.y);}
Point operator * (Point a, double b) {return Point(a.x * b, a.y * b);}

int n, m;
double ans = 0;
Point point[25];
Polygon polygon[25];

Vertical find(Point p) {

}

void solve() {
	queue<Line> q;
	for (int i = 1; i < m; i++) {
		q.push(Line(point[i], point[i + 1]));
		find(point[i]);
	}
	find(point[m]);
	while (!q.empty()) {
		Line t = q.front();
		q.pop();
		Point p1 = find(t.a).p;
		Point p2 = find(t.b).p;
		Point l = t.a, r = t.b, mid = (l + r) * 0.5;
		while ((r - l).len() > 1e-4) {
			Point m = (l + r) * 0.5;
			if ((m - p1).len() < (m - p2).len()) l = m;
			else r = m;
		}
		double tmp = max((l - p1).len(), (l - p2).len());
		find(l);
		if (ans + 0.005 > tmp) {
			q.push(Line(t.a, mid));
			q.push(Line(mid, t.b));
		}
	}
}

int main() {
	freopen("1020.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%lf %lf", &point[i].x, &point[i].y);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &polygon[i].cnt);
		for (int j = 1; j <= polygon[i].cnt; j++)
			scanf("%lf %lf", &polygon[i].p[j].x, &polygon[i].p[j].y);
	}
	solve();
	return 0;
}
