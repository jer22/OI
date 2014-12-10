/*
ID:shijiey1
PROG:fc
LANG:C++
*/

/*
裸的凸包。
graham-scan水过。
*/
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
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double multi(Point a, Point b, Point o) {
	// ab X ac
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int n;
Point p[10010];
int cmp(Point a, Point b) {
	double t = multi(a, b, p[0]);
	if (fabs(t) < 1e-8) return dist(p[0], a) < dist(p[0], b);
	return t > 0;
}

Point stack[10010];
int top = 0;
void grahamScan() {
	int t = 0;
	for (int i = 1; i < n; i++) {
		if (p[i].y < p[t].y || (p[i].y == p[t].y && p[i].x < p[t].x))
			t = i;
	}
	swap(p[0], p[t]);
	sort(p + 1, p + n, cmp);

	stack[0] = p[0];
	stack[1] = p[1];
	stack[2] = p[2];
	top = 2;
	for (int i = 3; i < n; i++) {
		while (top && multi(p[i], stack[top], stack[top - 1]) >= 0) {
			top--;
		} 
		stack[++top] = p[i];
	}
}

int main() {
	freopen("fc.in", "r", stdin);
	freopen("fc.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	grahamScan();


	stack[top + 1] = stack[0];
	//4 5 6 7       top=3
	double ans = 0;
	for (int i = 0; i <= top; i++) {
		ans += dist(stack[i], stack[i + 1]);
	}
	printf("%.2lf\n", ans);
	return 0;
}
