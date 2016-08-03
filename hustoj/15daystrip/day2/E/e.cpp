#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define eps 1e-8

using namespace std;

struct Point{
	double x, y;
	Point() {};
	Point(double a, double b) : x(a), y(b) {}
};

double rr;
int n;
Point p[1000005], ori;

double dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double multi(Point a, Point b, Point c) {
	// ab X ac
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

int cmp(Point a, Point b) {
	double t = multi(ori, a, b);
	if (fabs(t) < 1e-8) return dist(p[0], a) < dist(p[0], b);
	return t > 0;
}


int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%lf %lf %lf", &ori.x, &ori.y, &rr)) {
		if (scanf("%d", &n) == -1) break;
		int temp = 0;
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &a, &b);
			if (dist(Point(double(a), double(b)), ori) <= rr * rr)
				p[temp++] = Point(double(a), double(b));
		}
		n = temp;
		sort(p, p + n, cmp);

		int l = 0, r = 1;

		int ans = 0;
		for (l = 0; l < n; l++) {
			while (multi(ori, p[l], p[r]) >= 0 && r < n) r++;
			// cout << l << ' ' << r << endl;
			ans = max(ans, r - l);
		}
		cout << ans << endl;
	}


	return 0;
}
