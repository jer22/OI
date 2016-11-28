#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2005;

int n, p, u;
double a[MAXN], b[MAXN], ab[MAXN];
double dp[MAXN][MAXN];

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d %d %d", &n, &p, &u);
	for (int i = 0; i < n; i++)
		scanf("%lf", &a[i]);
	for (int i = 0; i < n; i++) {
		scanf("%lf", &b[i]);
		ab[i] = a[i] + b[i] - a[i] * b[i];
	}
	for (int i = 0; i < n; i++) {
		// memset(dp[i & 1], 0, sizeof(dp[i & 1]));
		for (int j = min(i, p); j >= max(0, p - n + i); j--) {
			for (int k = min(i, u); k >= max(0, u - n + i); k--) {
				dp[j + 1][k] = max(dp[j + 1][k], dp[j][k] + a[i]);
				dp[j][k + 1] = max(dp[j][k + 1], dp[j][k] + b[i]);
				dp[j + 1][k + 1] = max(dp[j + 1][k + 1], dp[j][k] + ab[i]);
			}
		}
	}
	cout << dp[p][u] << endl;

	return 0;
}
