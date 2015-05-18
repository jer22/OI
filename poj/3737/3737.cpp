#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-6;

double cal(double r, double s) {
	double L = (s - r * r * pi) / pi / r;
	double H = sqrt(L * L - r * r);
	return r * r * H * pi / 3.0;
}

int main() {
	// freopen("3737.in", "r", stdin);
	double s;
	while (~scanf("%lf", &s)) {
		double l = 0, r = sqrt(s / pi);
		while (l + eps < r) {
			double m1 = l + (r - l) / 3.0;
			double m2 = r - (r - l) / 3.0;
			double v1 = cal(m1, s);
			double v2 = cal(m2, s);
			if (v1 > v2) {
				r = m2;
			} else l = m1;
		}
		double L = (s - pi * r * r) / pi / r;
		double H = sqrt(L * L - r * r);
		double V = r * r * H * pi / 3.0;
		printf("%.2lf\n%.2lf\n%.2lf\n", V, H, r);
	}
	return 0;
}
