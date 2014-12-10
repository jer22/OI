/*
ID:shijiey1
LANG:C++
PROG:nuggets
*/

/*
所有方案都能满足的情况：当且仅当输入里的n个数里有1。否则1一定是一个解。
不存在不能满足的上限：计算出输入中最大的两个数的最小公倍数x，如果比x大的数有一个不能满足，则不存在不能满足的上限。
然后就是用背包问题统计某个数是否可以取到。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[11];
int limit;
int dp[69050];
int main() {
	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	arr[0] = 1;
	limit = arr[n] * arr[n - 1] + 10;
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = arr[i]; j <= limit; j++) {
			if (dp[j - arr[i]]) dp[j] = 1;
		}
	}
	for (int i = limit; i >= 1; i--) {
		if (!dp[i]) {
			if (i >= limit - 10) {
				printf("0\n");
				return 0;
			} else {
				printf("%d\n", i);
			}
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
