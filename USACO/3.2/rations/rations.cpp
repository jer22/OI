/*
ID:shijiey1
PROG:ratios
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int p[4], x[4], y[4], z[4];

int gcd(int a, int b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}

void scan() {
	for (int i = 1; i <= 3; i++) scanf("%d", &p[i]);
	for (int i = 1; i <= 3; i++) scanf("%d", &x[i]);
	for (int i = 1; i <= 3; i++) scanf("%d", &y[i]);
	for (int i = 1; i <= 3; i++) scanf("%d", &z[i]);
}

int main() {
	freopen("ratios.in", "r", stdin);
	freopen("ratios.out", "w", stdout);
	scan();
	int t = x[1] * y[2] * z[3] + x[3] * y[1] * z[2] + x[2] * y[3] * z[1]
		- x[3] * y[2] * z[1] - x[2] * y[1] * z[3] - x[1] * y[3] * z[2];
	if (!t) {
		printf("NONE\n");	
		return 0;
	}
	int a = p[1] * y[2] * z[3] + y[1] * z[2] * p[3] + z[1] * p[2] * y[3]
		- p[1] * z[2] * y[3] - p[2] * y[1] * z[3] - p[3] * y[2] * z[1];
	int b = x[1]*p[2]*z[3] + p[1]*z[2]*x[3] + z[1]*x[2]*p[3]
		-x[1]*z[2]*p[3] - p[1]*x[2]*z[3] - z[1]*p[2]*x[3];
	int c = x[1] * y[2] * p[3] + y[1] * p[2] * x[3] + y[3] * x[2] * p[1]
		-x[2] * y[1] * p[3] - y[2] * x[3] * p[1] - x[1] * y[3] * p[2];
	if (t < 0) {
		t = -t;
		a = -a;
		b = -b;
		c = -c;
	}
	if (a < 0 || b < 0 || c < 0) {
		printf("NONE\n");
		return 0;
	}
	int d = gcd(t, gcd(a, gcd(b, c)));
	printf("%d %d %d %d\n", a / d, b / d, c / d, t / d);
	return 0;
}
