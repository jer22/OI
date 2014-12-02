/*
ID:shijiey1
PROG:game1
LANG:C++
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
