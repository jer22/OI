#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

double a, c;
int b, d;
const double eps = 1e-8;
int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%lf %d %lf %d", &a, &b, &c, &d)) {
		double ans = 1.0;
		int t = 0;
		for (int i = 1; i <= b; i++) {
			ans *= a;
			if (t < d && ans > c) {
				ans /= c;
				t++;
			}
		}
		for (int i = t; i < d; i++)
			ans /= c;
		if (fabs(ans - 1.0) < eps) cout << "=" << endl;
		else if (ans - 1.0 > eps) cout << ">" << endl;
		else cout << "<" << endl;
	}


	return 0;
}
