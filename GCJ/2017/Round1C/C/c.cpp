#include <bits/stdc++.h>

using namespace std;
const double eps = 1e-11;

int T, n, k;
double rem;
double p[55];
int pp[55];

bool check(double x) {
	double tot = 0;
	for (int i = 1; i <= n; i++) {
		if (p[i] < x) tot += x - p[i];
	}
	return tot - eps < rem;
}

#define pr 10
double dp[5][55][50 * pr + 5];
int main() {
	freopen("c.in", "r", stdin);
	// freopen("c.out", "w", stdout);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &k);
		scanf("%lf", &rem);
		int remm = rem * pr;
		for (int i = 1; i <= n; i++) {
			scanf("%lf", &p[i]);
			pp[i] = p[i] * pr;
		}
		// double l = 0., r = 1.;
		// while (l + eps < r) {
		// 	double mid = (l + r) / 2;
		// 	if (check(mid)) {
		// 		l = mid;
		// 	} else r = mid;
		// }
		// for (int i = 1; i <= n; i++) {
		// 	if (p[i] < l) p[i] = l;
		// }
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i <= remm; i++) {
			double x = (double)i / pr;
			if (i > pr - pp[1]) break;
			double f = p[1] + x;
			dp[1][0][remm - i] = 1. - f;
			dp[1][1][remm - i] = f;
		}
		for (int i = 2; i <= n; i++) {
			// int now = i & 1;
			int now = i;
			// int pre = (i + 1) & 1;
			int pre = i - 1;
			memset(dp[now], 0, sizeof(dp[now]));
			for (int j = 0; j <= i; j++) {
				for (int k = 0; k <= remm; k++) {
					for (int l = k; l <= remm; l++) {
						if (l - k > pr - pp[i]) break;
						double f = double(pp[i] + l - k) / (double)pr;
						double t = 0;
						if (j > 0) t += dp[pre][j - 1][l] * f;
						if (j < i) t += dp[pre][j][l] * (1. - f);
						if (i == 2 && j == 1 && k == 0 && l == 10) {
							// cout << dp[pre][j - 1][l] << endl;
						}
						dp[now][j][k] = max(dp[now][j][k], t);
					}

				}
			}
		}

		cout << dp[2][1][0] << endl;
		double ans = 0.;
		for (int i = k; i <= n; i++)
			ans += dp[n][i][0];
		printf("Case #%d: %.10lf\n", cas, ans);
	}
	

	return 0;
}
