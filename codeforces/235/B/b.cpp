#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

int n;
double p;
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &n);
	double len = 0;
	double ans = 0;
	for (int i = 1; i <= n; i++) {
		double x;
		scanf("%lf", &x);
		ans += (2 * len + 1) * x;
		len = (len + 1) * x;
	}
	printf("%.10lf\n", ans);
	return 0;
}
