#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;
const double eps = 1e-7;

int T, n;
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		double x;
		int cnt0 = 0, cnt1 = 0;
		double sum = 0;
		for (int i = 1; i <= n << 1; i++) {
			scanf("%lf", &x);
			double a = x - int(x);
			if (fabs(a) > eps) cnt1++;
			else cnt0++;
			sum += a;
		}
		double ans = 1e30;
		for (int i = 0; i <= n; i++) {
			//choose i x (.xxx) ans (n - i) x (.000)
			if (cnt1 >= i && cnt0 >= n - i) {
				ans = min(ans, fabs(sum - i));
			}
		}
		printf("%.3lf\n", ans);
	}

	return 0;
}
