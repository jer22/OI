#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;


double dp[2005][2005];

double dfs(int k, int w) {
	if (!k) return 0.0;
	if (!w) return 1000000000.0;
	if (fabs(dp[k][w] - 1000000000.0) > 1e-8) return dp[k][w];
	for (int i = 1; i <= k; i++) {
		double a = double(i) / double(k + 1);
		double b = double(k - i + 1) / double(k + 1);
		// sum += b * dfs(k - i, w) + a * dfs(i - 1, w - 1) + 1.0;
		dp[k][w] = min(dp[k][w], b * dfs(k - i, w) + a * dfs(i - 1, w - 1) + 1.0);
	}
	return dp[k][w];
}

int K, w;
int main() {
	freopen("1001.in", "r", stdin);
	w = min(w, (int)log2(K) + 1);
	for (int i = 0; i <= 2000; i++)
		for (int j = 0; j <= 2000; j++)
			dp[i][j] = 1000000000.0;
	dp[1][1] = 1.0;
	for (int i = 1; i <= 2000; i++) {
		for (int j = 1; j <= 2000; j++) {
			dp[i][j] = dfs(i, min(j, (int)log2(i) + 1));
		}
	}
	while (~scanf("%d %d", &K, &w)) {
		printf("%.6lf\n", dp[K][w]);
	}


	return 0;
}
