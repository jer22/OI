#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double pi = acos(-1);
const double eps = 1e-8;

int T;
double n, len, r;

double getx() {
	double theta = (90 - 180 / n) * pi / 180;
	return len * tan(theta);
}

int main() {
	freopen("1004.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		cin >> n >> len >> r;
		double x = getx();
		r *= 2;
		printf("Case #%d:\n", cas++);
		if (r + eps <= x) printf("Give me a kiss!\n");
		else printf("I want to kiss you!\n");
	}


	return 0;
}
