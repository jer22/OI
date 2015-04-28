#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

double a, b, c, d, e, f;
int dir[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

double getz(double x, double y) {
	double A = c;
	double B = e * x + d * y;
	double C = a * x * x + b * y * y + f * x * y - 1;
	double delta = B * B - 4 * A * C;
	if (delta < 0) return 1e60;
	double z1 = (-B + sqrt(delta)) / (A * 2);
	double z2 = (-B - sqrt(delta)) / (A * 2);
	if (z1 * z1 < z2 * z2) return z1;
	return z2;
}

double dis(double x, double y, double z) {
	return sqrt(x * x + y * y + z * z);
}

double solve() {
	double t = 1;
	double x = 0, y = 0;
	double ans;
	while (t > 1e-8) {
		double z = getz(x, y);
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 8; i++) {
				double nx = x + t * dir[i][0];
				double ny = y + t * dir[i][1];
				double nz = getz(nx, ny);
				if (nz > 1e30) continue;
				if (dis(nx, ny, nz) < dis(x, y, z)) {
					ans = dis(nx, ny, nz);
					x = nx, y = ny, z = nz;
				}
			}
		}
		t *= 0.99;
	}
	return ans;
}

int main() {
	freopen("k.in", "r", stdin);
	while (cin >> a >> b >> c >> d >> e >> f) {
		double ans = solve();
		printf("%.8lf\n", ans);
	}
	return 0;
}
