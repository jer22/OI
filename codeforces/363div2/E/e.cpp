#include <bits/stdc++.h>

using namespace std;

int n, k;
double p[25], ans[25], dp[1 << 20];
int main() {
	freopen("e.in", "r", stdin);
	cin >> n >> k;
	int nz = 0;
	for (int i = 0; i < n; i++) {
		cin >> p[i];
		if (p[i] <= 1e-9) nz++;
	}
	if (n - nz <= k) {
		for (int i = 0; i < n; i++)
			if (p[i] <= 1e-9) ans[i] = 0.0;
			else ans[i] = 1.0;
	} else {
		dp[0] = 1;
		for (int i = 0; i < 1 << n; i++) {
			int cnt = __builtin_popcount(i);
			if (cnt > k) continue;
			if (cnt == k) {
				for (int j = 0; j < n; j++)
					if (i & (1 << j)) ans[j] += dp[i];
				continue;
			}
			double tot = 0;
			for (int j = 0; j < n; j++)
				if (!(i & (1 << j))) tot += p[j];
			for (int j = 0; j < n; j++)
				if (!(i & (1 << j))) dp[i | (1 << j)] += dp[i] * p[j] / tot;
		}

	}
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%.10lf", ans[i]);
	}
	printf("\n");


	return 0;
}
