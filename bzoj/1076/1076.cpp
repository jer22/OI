#include <bits/stdc++.h>

using namespace std;

int n, m;
double dp[105][33000];
int val[105];
int pre[105];

int main() {
	freopen("1076.in", "r", stdin);
	scanf("%d %d", &n, &m);
	int a;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &val[i], &a);
		while (a) {
			pre[i] |= (1 << (a - 1));
			scanf("%d", &a);
		}
	}
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < 1 << m; j++) {
			for (int k = 0; k < m; k++) {
				if ((pre[k] & j) == pre[k]) {
					dp[i][j] += max(dp[i + 1][j], dp[i + 1][j | (1 << k)] + val[k]);
				} else dp[i][j] += dp[i + 1][j];
			}
			dp[i][j] /= m;
		}
	}
	printf("%.6lf\n", dp[1][0]);


	return 0;
}
