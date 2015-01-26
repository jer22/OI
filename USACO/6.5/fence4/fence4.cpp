/*
ID:shijiey1
LANG:C++
PROG:fence4
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Point{
	double x, y;
	Point() {}
	Point(double a, double b) : x(a), y(b) {}
};

struct Line{
	Point a, b;
	Line() {}
	Line(Point c, Point d) : a(c), b(d) {}
};

int n;
double sx, sy;
Point s;
Point point[205];
Line line[205];
int cnt[205];

double multi(Point a, Point b, Point o) {
	return double(a.x - o.x) * double(b.y - o.y) - double(a.y - o.y) * double(b.x - o.x);
}

bool cross(Line a, Line b) {
	double x = multi(b.b, a.a, b.a);
	double y = multi(b.b, a.b, b.a);
	if (x * y >= 0) return 0;
	x = multi(a.b, b.a, a.a);
	y = multi(a.b, b.b, a.a);
	if (x * y >= 0) return 0;
	return 1;
}

bool check() {
	for (int i = 0; i < n - 1; i++)
		line[i] = Line(point[i], point[i + 1]);
	line[n - 1] = Line(point[0], point[n - 1]);
	swap(line[n - 2], line[n - 1]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++) {
			if (abs(i - j) == 1 || (i == n - 1 && j == 0)) continue;
			// cout << i << ' ' << j << ' ' << cross(line[i], line[j]) << endl;
			if (cross(line[i], line[j]) == 1)  {cout << i << ' ' << j << endl;return false;}
		}
	return true;
}

double getDist(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int getNear(double x, double y) {
	double near = 10000000.0;
	int idx = -1;
	for (int j = 0; j < n; j++) {
		// if (cnt[j] > 2) continue;
		if (cross(line[j], Line(Point(x, y), s)) == 0) continue;
		if ((line[j].a.y - sy) * (line[j].b.x - sx) == (line[j].b.y - sy) * (line[j].a.x - sx)) continue;
		double k2 = 1.0;
		double k1 = multi(line[j].a, line[j].b, s) / multi(line[j].b, line[j].a, Point(x, y));
		double cx = (k2 * sx + k1 * x) / (k1 + k2);
		double cy = (k2 * sy + k1 * y) / (k1 + k2);
		double dist = getDist(sx, sy, cx, cy);
		if (dist < near) {
			near = dist;
			idx = j;
		}
	}
	return idx;
}

int main() {
	freopen("fence4.in", "r", stdin);
	freopen("fence4.out", "w", stdout);
	scanf("%d", &n);
	cin >> sx >> sy;
	s = Point(sx, sy);
	for (int i = 0; i < n; i++)
		cin >> point[i].x >> point[i].y;
	if (!check())
		printf("NOFENCE\n");
	else {
		int part = 15000;
		double x = sx, y = sy + part;
		double t = 1;
		for (int i = 0; i < 4 * part; i++) {
			if (x == sx + part) t = -1;
			if (x == sx - part) t = 1;
			x += t;
			y = sqrt(double(part * part - (x - sx) * (x - sx))) + sy;
			y *= t;
			// cout << cross(Line(Point(10, 10), Point(x, y)), Line(Point(50, 10), Point(50, 9)));
			int idx = getNear(x, y);
			
			if (idx != -1) cnt[idx]++;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		// cout << cnt[i] << endl;
		if (cnt[i] >= 2) ans++;
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++) {
		if (cnt[i] >= 2)
			printf("%d %d %d %d\n", (int)line[i].a.x, (int)line[i].a.y, (int)line[i].b.x, (int)line[i].b.y);
	}
	return 0;
}
