#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Point {
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return y < p.y;
	}
};

int n, w, bus, per;
Point p[10005];

bool check() {
	for (int i = 1; i <= n; i++) {
		if (p[i].x < 0) continue;
		double tim = (double)p[i].x / (double)bus;
		double t1 = (double)p[i].y / (double)per;
		if (tim < t1) {
			return false;
		}
	}
	return true;
}

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n >> w >> bus >> per;
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &p[i].x, &p[i].y);
	if (check()) {
		printf("%.10lf\n", double(w) / double(per));
		return 0;
	}
	sort(p + 1, p + n + 1);
	double now = 0.0;
	double way = 0;
	int man = 0;
	for (int i = 1; i <= n; i++) {
		if ((double)p[i].x - way < 0) continue;
		double bustim = (double(p[i].x) - way) / double(bus);
		double mantim = double(p[i].y - man) / double(per);
		if (bustim > mantim) {
			now += bustim;
			man = p[i].y;
			way = double(p[i].x);
		} else {
			now += mantim;
			man = p[i].y;
			way += mantim * bus;
		}
	}
	now += (double(w) - man) / (double)per;
	printf("%.10lf\n", now);

	return 0;
}
