#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Point{
	long long x, y;
	Point() {}
	Point(long long a, long long b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		if (x != p.x) return x < p.x;
		return y > p.y;
	}
};

int n;
long long f[50005], q[50005];
Point b[50005], a[50005];
int main() {
	freopen("1597.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		cin >> b[i].x >> b[i].y;
	sort(b, b + n);
	int m = 0;
	for (int i = 0; i < n; i++) {
		while (m && a[m].y < b[i].y) m--;
		a[++m] = b[i];
	}
	int h = 1, t = 1;
	for (int i = 1; i <= m; i++) {
		while (h < t && (a[i].x * (a[q[h] + 1].y - a[q[h + 1] + 1].y) > f[q[h + 1]] - f[q[h]])) h++;
		f[i] = f[q[h]] + a[q[h] + 1].y * a[i].x;
		while (h < t && (f[i] - f[q[t - 1]]) * (a[q[t] + 1].y - a[i + 1].y) >= (f[i] - f[q[t]]) * (a[q[t - 1] + 1].y - a[i + 1].y)) t--;
		q[++t] = i;
	}
	cout << f[m] << endl;
	return 0;
}
