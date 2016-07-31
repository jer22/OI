#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

#define eps 1e-8

using namespace std;

int n, k;
double l, v1, v2;
int main() {
	// freopen("d.in", "r", stdin);
	cin >> n >> l >> v1 >> v2 >> k;
	double ans = 0.0;
	int t = n / k;
	if (n % k) t++;
	t--;
	double a = ((double)t * 2.0 * v2 * v1) / (v1 + v2) + v2;
	double x = l / a;
	double y = (l - x * v2) / v1;
	printf("%.10lf\n", x + y);

	return 0;
}
