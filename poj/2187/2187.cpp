#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 50005

using namespace std;

struct Point{
	long long x, y;
	Point() {}
	Point(long long a, long long b) : x(a), y(b) {}
};

int n;
Point p[MAXN];
Point stack[MAXN << 1];
int top = 0;

long long dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

long long multi(Point a, Point b, Point c) {
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

int cmp(Point a, Point b) {
	long long t = multi(p[0], a, b);
	if (!t) return dist(p[0], a) < dist(p[0], b);
	return t > 0;
}

void graham() {
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
		while (multi(stack[top - 2], stack[top - 1], p[i]) < 0) {
			top--;
		}
		stack[top++] = p[i];
	}
}

int main() {
	freopen("2187.in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%lld %lld", &p[i].x, &p[i].y);
	graham();
	for (int i = top; i < top + top; i++)
		stack[i] = stack[i - top];
	n = top << 1;
	int t = 0;
	long long best = -0x3f3f3f3f;
	for (int i = 0; i < top; i++) {
		for (int j = i + 1; j < top; j++) {
			best = max(best, dist(stack[i], stack[j]));
		}
	}
	cout << best << endl;
	return 0;
}
