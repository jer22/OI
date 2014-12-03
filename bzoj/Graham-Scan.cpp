#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Point {
	double x, y;
};

double dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

double multi(Point a, Point b, Point c) {
	// ab X ac
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

int n;
Point p[100];
int cmp(Point a, Point b) {
	double t = multi(p[0], a, b);
	if (fabs(t) < 1e-8) return dist(p[0], a) < dist(p[0], b);
	return t > 0;
}

Point stack[100];
int top = 0;
void grahamScan() {
	int t = 0;
	for (int i = 1; i < n; i++) {
		if (p[i].y < p[t].y || (p[i].y == p[t].y && p[i].x < p[t].x))
			t = i;
	}
	swap(p[0], p[t]);
	sort(p + 1, p + n, cmp);
	stack[top++] = p[0];
	stack[top++] = p[1];
	stack[top++] = p[2];
	for (int i = 3; i < n; i++) {
		while (multi(stack[top - 2], stack[top - 1], p[i]) <= 0) {
			top--;
		}
		stack[top++] = p[i];
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	grahamScan();
	Point s = stack[--top];
	double ans = 0;
	while (top--) {
		ans += sqrt(dist(stack[top], stack[top + 1]));
	}
	
	ans += sqrt(dist(s, stack[0]));
	printf("%.2lf\n", ans);
	return 0;
}
