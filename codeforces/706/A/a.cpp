#include <bits/stdc++.h>

using namespace std;

int n;
double a, b, c;
double x, y;

double dist(int a, int b, int c, int d) {
	return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

int main() {
	freopen("a.in", "r", stdin);
	cin >> x >> y;
	cin >> n;
	double ans = 10000000000000;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> c;
		ans = min(ans, dist(a, b, x, y) / c);
	}
	printf("%.10lf\n", ans);

	return 0;
}
