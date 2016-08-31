#include <bits/stdc++.h>

using namespace std;

int T, n;
double p, q;
double f[105], g[105];
int main() {
	freopen("2318.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %lf %lf", &n, &p, &q);
		n = min(n, 100);
		f[0] = 0;
		g[0] = 1;
		for (int i = 1; i <= n; i++) {
			double a = p, b = q;
			if (f[i - 1] > g[i - 1]) {
				a = 1 - a;
				b = 1 - b;
			}
			f[i] = (a * g[i - 1] + (1 - a) * b * f[i - 1]) / (1 - (1 - a) * (1 - b));
			g[i] = (b * f[i - 1] + (1 - b) * a * g[i - 1]) / (1 - (1 - b) * (1 - a));
		}
		printf("%.6lf\n", f[n]);

	}


	return 0;
}
