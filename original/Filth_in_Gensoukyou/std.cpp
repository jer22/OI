#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int T, n;
double ff[MAXN];

int main() {
	freopen("filth.in", "r", stdin);
	freopen("filth.out", "w", stdout);
	scanf("%d", &T);
	for (int i = 1; i <= 1000000; i++) {
		ff[i] = ff[i - 1] + 1. / i;
	}
	while (T--) {
		scanf("%d", &n);
		double ans = double(n + 1) * ff[n] - n;
		printf("%.10lf\n", ans * 2 - n);
	}

	return 0;
}
