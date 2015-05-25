#include <bits/stdc++.h>

using namespace std;

const int MAXN = 505;
const double eps = 1e-6;

struct Point{
	double x, y;
	Point() {}
	Point(double a, double b) : x(a), y(b) {}
};

struct Line{
	Point p1, p2;
	double k, b;
	Line() {}
	Line(double x1, double y1, double x2, double y2) {
		p1 = Point(x1, y1);
		p2 = Point(x2, y2);
		k = (y1 - y2) / (x1 - x2);
		b = y1 - k * x1;
	}
	double f(double x) {
		return x * k + b;
	}
};

struct Cir{
	double x, r;
};

int n, tot;
double alpha;
Cir circle[MAXN];
Line lines[MAXN];

double f(double x) {
	double re = 0;
	for (int i = 1; i <= n; i++) {
		double dis = fabs(x - circle[i].x);
		if (dis - circle[i].r > -eps) continue;
		double y = sqrt(circle[i].r * circle[i].r - dis * dis);
		re = max(re, y);
	}
	for (int i = 1; i <= tot; i++)
		if (x >= lines[i].p1.x && x <= lines[i].p2.x)
			re = max(re, lines[i].f(x));
	return re;
}

double simpson(double fl, double fr, double fmid, double h) {
	return h * (fl + 4 * fmid + fr) / 6.0;
}

double getarea(double l, double r, double mid, double fl, double fr, double fmid, double area) {
	double lmid = (l + mid) / 2.0;
	double rmid = (r + mid) / 2.0;
	double flmid = f(lmid);
	double frmid = f(rmid);
	double larea = simpson(fl, fmid, flmid, mid - l);
	double rarea = simpson(fmid, fr, frmid, r - mid);
	if (fabs(larea + rarea - area) < eps) return area;
	return getarea(l, mid, lmid, fl, fmid, flmid, larea) + getarea(mid, r, rmid, fmid, fr, frmid, rarea);
}

int main() {
	freopen("1502.in", "r", stdin);
	scanf("%d %lf", &n, &alpha);
	n++;
	alpha = 1 / tan(alpha);
	for (int i = 1; i <= n; i++) {
		scanf("%lf", &circle[i].x);
		circle[i].x *= alpha;
		circle[i].x += circle[i - 1].x;
	}
	for (int i = 1; i < n; i++)
		scanf("%lf", &circle[i].r);
	double l = 1e20, r = -1;
	for (int i = 1; i <= n; i++) {
		l = min(l, circle[i].x - circle[i].r);
		r = max(r, circle[i].x + circle[i].r);
	}
	for (int i = 2; i <= n; i++) {
		double L = circle[i].x - circle[i - 1].x;
		if (L - fabs(circle[i - 1].r - circle[i].r) < eps) continue;
		double sina = (circle[i - 1].r - circle[i].r) / L;
		double cosa = sqrt(1 - sina * sina);
		lines[++tot] = Line(circle[i - 1].x + circle[i - 1].r * sina, circle[i - 1].r * cosa,
			circle[i].x + circle[i].r * sina, circle[i].r * cosa);
	}
	double mid = (l + r) / 2;
	double fl = f(l);
	double fr = f(r);
	double fmid = f(mid);
	printf("%.2lf\n", 2 * getarea(l, r, mid, fl, fr, fmid, simpson(fl, fr, fmid, r - l)));

	return 0;
}
