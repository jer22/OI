/*
ID:shijiey1
PROG:game1
LANG:C++
*/

/*
设两玩家分别为p1，p2。
状态：dp[l][r]:序列还剩[l,r]时先手取的最大得分
则现在有两种选择：取l和取r。
若取l，下一步换另一个人取的最大得分为dp[l+1][r],所以这一步的最大得分dp[l][r]=sum[l,r]-dp[l+1][r]
若取r同理。即dp[l][r] = max(sum[l,r]-dp[l + 1][r], sum[l][r]-dp[l][r+1])；
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int arr[105];
int dp[105][105];
int sum[105];

int getSum(int l, int r) {
	return sum[r] - sum[l - 1];
}

int dfs(int l, int r) {
	if (dp[l][r]) return dp[l][r];
	if (l == r) {
		dp[l][r] = arr[l];
		return dp[l][r];
	}
	int ans = max(getSum(l, r) - dfs(l + 1, r), getSum(l, r) - dfs(l, r - 1));
	dp[l][r] = ans;
	return ans;
}

int main() {
	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		sum[i] = sum[i - 1] + arr[i];
	}
	int ans = dfs(1, n);
	printf("%d %d\n", ans, getSum(1, n) - ans);

	return 0;
}
