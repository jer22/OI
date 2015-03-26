#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
long long dp[5][2505];
int main() {
	freopen("1600.in", "r", stdin);
	scanf("%d", &n);
	int mx = (n + 1 >> 1) - 1;
	dp[0][0] = 1;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= n; j++)
			for (int k = 1; k <= min(j, mx); k++)
				dp[i][j] += dp[i - 1][j - k];
	printf("%lld\n", dp[4][n]);
	return 0;
}
