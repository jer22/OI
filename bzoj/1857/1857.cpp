#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1);
const double eps = 1e-8;

double ax, ay, bx, by, cx, cy, dx, dy;
double p, q, r;
double dist(double x1, double y1, double x2, double y2) {
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double cal(double x1, double y1, double x2, double y2) {
	double d1 = dist(ax, ay, x1, y1);
	double d2 = dist(x1, y1, x2, y2);
	double d3 = dist(x2, y2, dx, dy);
	return d1 / p + d2 / r + d3 / q;
}

double solve(double x, double y) {
	double lx = cx, rx = dx;
	double ly = cy, ry = dy;
	while (fabs(rx - lx) > eps || fabs(ry - ly) > eps) {
		double x1 = lx + (rx - lx) / 3.0;
		double x2 = rx - (rx - lx) / 3.0;
		double y1 = ly + (ry - ly) / 3.0;
		double y2 = ry - (ry - ly) / 3.0;
		double v1 = cal(x, y, x1, y1);
		double v2 = cal(x, y, x2, y2);
		if (v1 > v2) lx = x1, ly = y1;
		else rx = x2, ry = y2;
	}
	return cal(x, y, lx, ly);
}

int main() {
	// freopen("1857.in", "r", stdin);
	scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
	scanf("%lf %lf %lf %lf", &cx, &cy, &dx, &dy);
	scanf("%lf %lf %lf", &p, &q, &r);
	double lx = ax, rx = bx;
	double ly = ay, ry = by;
	while (fabs(rx - lx) > eps || fabs(ry - ly) > eps) {
		double x1 = lx + (rx - lx) / 3.0;
		double x2 = rx - (rx - lx) / 3.0;
		double y1 = ly + (ry - ly) / 3.0;
		double y2 = ry - (ry - ly) / 3.0;
		double v1 = solve(x1, y1);
		double v2 = solve(x2, y2);
		if (v1 > v2) lx = x1, ly = y1;
		else rx = x2, ry = y2;
	}
	printf("%.2lf\n", solve(lx, ly));
	return 0;
}
