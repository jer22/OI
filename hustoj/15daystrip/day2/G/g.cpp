#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double eps = 1e-18;
const double INF = 1e30;

int n;
double par[105][3];

struct Point{
	double x, y;
	Point() {}
	Point(double a, double b) : x(a), y(b) {}
};

struct Line{
	double a, b, c;
	Line() {}
	Line(double d, double e, double f) : a(d), b(e), c(f) {}
};

int tot;
Point p[1005], q[1005];

Point getInter(Point p1, Point p2, double a, double b, double c) {
	double u = fabs(a * p1.x + b * p1.y + c);
	double v = fabs(a * p2.x + b * p2.y + c);
	Point ans;
	ans.x = (p1.x * v + p2.x * u) / (u + v);
	ans.y = (p1.y * v + p2.y * u) / (u + v);
	return ans;
}

void cut(double a, double b, double c) {
	int t = 0;
	for (int i = 1; i <= tot; i++) {
		if (a * p[i].x + b * p[i].y + c < eps) q[++t] = p[i];
		else {
			if (a * p[i - 1].x + b * p[i - 1].y + c < -eps)
				q[++t] = getInter(p[i], p[i - 1], a, b, c);
			if (a * p[i + 1].x + b * p[i + 1].y + c < -eps)
				q[++t] = getInter(p[i], p[i + 1], a, b, c);
		}
	}
	for (int i = 1; i <= t; i++)
		p[i] = q[i];
	p[0] = p[t];
	p[t + 1] = p[1];
	tot = t;
}

double calcarea() {
	double area = 0.0;
	for (int i = 1; i <= tot; i++) {
		area += p[i].x * p[i + 1].y - p[i].y * p[i + 1].x;
	}
	return area;
}

bool check(int i) {
	p[5] = p[1] = Point(0, 0);
	p[2] = Point(INF, 0);
	p[3] = Point(INF, INF);
	p[0] = p[4] = Point(0, INF);
	tot = 4;

	for (int j = 0; j < n; j++) {
		if (j == i) continue;
		double a = (par[j][0] - par[i][0]) / (par[i][0] * par[j][0]);
		double b = (par[j][1] - par[i][1]) / (par[i][1] * par[j][1]);
		double c = (par[j][2] - par[i][2]) / (par[i][2] * par[j][2]);
		if (fabs(a) < eps && fabs(b) < eps) {
			if (c >= 0) return false;
			else continue;
		}
		cut(a, b, c);
	}
	if (fabs(calcarea()) < eps) return false;
	return true;
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf %lf", &par[i][0], &par[i][1], &par[i][2]);
	for (int i = 0; i < n; i++) {
		if (check(i)) printf("Yes\n");
		else printf("No\n");
	}


	return 0;
}
