#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXN = 1005;

struct Point{
	double x, y;
}p[MAXN];

int T, n;
double t[MAXN];

double dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
	freopen("i.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		double ans = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%lf %lf %lf", &t[i], &p[i].x, &p[i].y);
			if (i == 1) continue;
			double tmp = sqrt(dist(p[i], p[i - 1])) / (t[i] - t[i - 1]);
			ans = max(ans, tmp);
		}
		printf("%.10lf\n", ans);
	}


	return 0;
}
