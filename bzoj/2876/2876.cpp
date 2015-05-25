#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10005;
const double eps = 1e-12;
const double INF = 1e9;

int n;
double E;
double s[MAXN], k[MAXN], vv[MAXN];
double v[MAXN];

double cal(double lambda) {
	double tot = 0;
	for (int i = 0; i < n; i++) {
		double l = max(0.0, vv[i]), r = INF;
		while (l + eps < r) {
			double mid = (l + r) / 2;
			v[i] = mid;
			if (2 * lambda * k[i] * v[i] * v[i] * (v[i] - vv[i]) < 1) l = mid;
			else r = mid;
		}
		v[i] = (l + r) / 2;
		tot += k[i] * (v[i] - vv[i]) * (v[i] - vv[i]) * s[i];
	}
	return tot;
}

int main() {
	scanf("%d %lf", &n, &E);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf %lf", &s[i], &k[i], &vv[i]);
	double l = 0, r = INF;
	while (l + eps < r) {
		double mid = (l + r) / 2;
		if (cal(mid) >= E) l = mid;
		else r = mid;
	}
	double ans = 0;
	for (int i = 0; i < n; i++)
		ans += s[i] / v[i];
	printf("%.6lf\n", ans);
	return 0;
}
