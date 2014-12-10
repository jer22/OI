/*
ID:shijiey1
PROG:subset
LANG:C++
*/

/*
01背包水题。
如果集合中数字之和是奇数则直接输出0，否则就按背包的思路做。统计正好花费sum/2时的方案数。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, sum = 0;
long long dp[50][5000];
int main() {
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) sum += i;
	if (sum % 2) {
		printf("0\n");
		return 0;
	}
	memset(dp, 0, sizeof(dp));
	dp[1][1] = 1;
	dp[1][0] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 0; j <= sum; j++) {
			if (j >= i && dp[i - 1][j - i] != 0)
				dp[i][j] += dp[i - 1][j - i];
			if (dp[i - 1][j] != 0)
				dp[i][j] += dp[i - 1][j];
		}
	}
	printf("%lld\n", dp[n][sum / 2] / 2);
	return 0;
}
