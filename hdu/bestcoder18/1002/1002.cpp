#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

double a, b, c, d, l, r;
double aa, bb, cc;
int main() {
	freopen("1002.in", "r", stdin);
	while (cin >> a >> b >> c >> d >> l >> r) {
		aa = 3 * a;
		bb = 2 * b;
		cc = c;
		if (!aa) {
			if (!bb) {
				double t3 = abs(a * l * l * l + b * l * l + c * l + d);
				double t4 = abs(a * r * r * r + b * r * r + c * r + d);
				printf("%.2f\n", max(t3, t4));
				continue;
			}
			double t1 = (cc / bb) * (-1);
			if (t1 < l || t1 > r) {
				t1 = l;
			}
			double t2 = abs(a * t1 * t1 * t1 + b * t1 * t1 + c * t1 + d);
			double t3 = abs(a * l * l * l + b * l * l + c * l + d);
			double t4 = abs(a * r * r * r + b * r * r + c * r + d);
			printf("%.2f\n", max(t2, max(t3, t4)));
			continue;
		}
		double t = bb * bb - 4 * aa * cc;
		if (t >= 0) {
			

			double t1 = ((bb * (-1)) + sqrt(t)) / (aa * 2);
			double t2 = ((bb * (-1)) - sqrt(t)) / (aa * 2);
			if (t1 < l || t1 > r) {
				t1 = l;
			}
			if (t2 < l || t2 > r) {
				t2 = l;
			}
			double t5 = abs(a * t1 * t1 * t1 + b * t1 * t1 + c * t1 + d);
			double t6 = abs(a * t2 * t2 * t2 + b * t2 * t2 + c * t2 + d);
			double t3 = abs(a * l * l * l + b * l * l + c * l + d);
			double t4 = abs(a * r * r * r + b * r * r + c * r + d);
			printf("%.2f\n", max(max(t3, t4), max(t5, t6)));
			continue;
		}
		double t1 = abs(a * l * l * l + b * l * l + c * l + d);
		double t2 = abs(a * r * r * r + b * r * r + c * r + d);
		printf("%.2f\n", max(t1, t2));
	}
	return 0;
}
