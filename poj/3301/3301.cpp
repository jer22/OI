#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-8;
const double INF = 1000000;

struct Point{
	double x, y;
};

int T, n;
Point p[35];

double cal(double phi) {
	double maxx = -INF, maxy = -INF;
	double minx = INF, miny = INF;
	for (int i = 0; i < n; i++) {
		double x = p[i].x * cos(phi) - p[i].y * sin(phi);
		double y = p[i].x * sin(phi) + p[i].y * cos(phi);
		maxx = max(maxx, x);
		maxy = max(maxy, y);
		minx = min(minx, x);
		miny = min(miny, y);
	}
	return max((maxx - minx) * (maxx - minx), (maxy - miny) * (maxy - miny));
}

int main() {
	// freopen("3301.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &p[i].x, &p[i].y);
		double l = 0.0, r = pi / 2;
		while (l + eps < r) {
			double m1 = l + (r - l) / 3.0;
			double m2 = r - (r - l) / 3.0;
			double v1 = cal(m1);
			double v2 = cal(m2);
			if (v1 < v2) r = m2;
			else l = m1;
		}
		printf("%.2lf\n", cal(l));;
	}
	return 0;
}
