#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 50005

using namespace std;

int n;
long long L;
long long sum[MAXN];
long long f[MAXN];
long long dp[MAXN];
int q[MAXN];
long long G(int x, int y) {
	return dp[x] + (f[x] + L) * (f[x] + L) - dp[y] - (f[y] + L) * (f[y] + L);
}

long long S(int x, int y) {
	return f[x] - f[y] << 1;
}

int main() {
	freopen("1010.in", "r", stdin);
	scanf("%d %lld", &n, &L);
	L++;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &sum[i]);
		sum[i] += sum[i - 1];
		f[i] = sum[i] + (long long)i;
	}
	int h = 1, t = 2;
	q[1] = 0;
	for (int i = 1; i <= n; i++) {
		while (h < t - 1 && G(q[h + 1], q[h]) <= S(q[h + 1], q[h]) * f[i]) h++;
		dp[i] = dp[q[h]] + (f[i] - f[q[h]] - L) * (f[i] - f[q[h]] - L);
		while (h < t - 1 && G(i, q[t - 1]) * S(q[t - 1], q[t - 2]) <= G(q[t - 1], q[t - 2]) * S(i, q[t - 1])) t--;
		q[t++] = i;
	}
	printf("%lld\n", dp[n]);

	return 0;
}
