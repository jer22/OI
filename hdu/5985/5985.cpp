#include <bits/stdc++.h>

using namespace std;

int T, n;
int cnt[15];
double p[15];

double power(double a, int b) {
	double ans = 1.;
	while (b) {
		if (b & 1) ans *= a;
		a *= a;
		b >>= 1;
	}
	return ans;
}

double f[10005][15];
int main() {
	freopen("5985.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %lf", &cnt[i], &p[i]);
		if (n == 1) {
			printf("1.000000\n");
			continue;
		}
		memset(f, 0, sizeof(f));
		for (int i = 0; i < n; i++)
			for (int j = 1; j <= 10000; j++)
				f[j][i] = 1. - power(1. - power(p[i], j), cnt[i]);
		for (int i = 0; i < n; i++) {
			double ans = 0.;
			for (int j = 1; j < 1000; j++) {
				double t = 1.;
				for (int k = 0; k < n; k++) {
					if (k == i) continue;
					t *= (1. - f[j][k]);
				}
				ans += t * (f[j][i] - f[j + 1][i]);
			}
			if (i) printf(" ");
			printf("%.6lf", ans);
		}
		printf("\n");
	}

	return 0;
}
