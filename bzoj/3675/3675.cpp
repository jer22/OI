#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

int n, K;
long long sum[MAXN];
long long dp[MAXN][2];
long long y[MAXN][2];
int q[MAXN], h, t;
int idx = 0;

int main() {
	// freopen("3675.in", "r", stdin);
	scanf("%d %d", &n, &K);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &sum[i]);
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i <= n; i++)
		y[i][0] = sum[i] * sum[i];
	for (int j = 1; j <= K; j++) {
		idx ^= 1;
		h = t = 1;
		q[h] = 0;
		for (int i = 1; i <= n; i++) {
			while (h < t && sum[i] * (sum[q[h + 1]] - sum[q[h]]) >= (y[q[h + 1]][idx ^ 1] - y[q[h]][idx ^ 1])) h++;
			dp[i][idx] = dp[q[h]][idx ^ 1] + sum[i] * sum[q[h]] - sum[q[h]] * sum[q[h]];
			y[i][idx] = sum[i] * sum[i] - dp[i][idx];
			while (h < t && (y[q[t]][idx ^ 1] - y[q[t - 1]][idx ^ 1]) * (sum[i] - sum[q[t]]) >= (y[i][idx ^ 1] - y[q[t]][idx ^ 1]) * (sum[q[t]] - sum[q[t - 1]])) t--;
			q[++t] = i;
		}
	}
	printf("%lld\n", dp[n][idx]);
	return 0;
}
