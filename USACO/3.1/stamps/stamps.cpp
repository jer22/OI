/*
ID:shijiey1
PROG:stamps
LANG:C++
*/

/*
dp[i]表示要得到i元钱需要几张邮票。
初始状态：dp[0]=0
然后递推，对于每一个dp[i]<5枚举每一张邮票的价值w，dp[i+w]=dp[i]+1.
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
int arr[65];
int dp[2000010];

int min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int main() {
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
	scanf("%d %d", &m, &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	int i;
	for (i = 0; i < 2000010; i++) {
		if (dp[i] > m) break;
		for (int j = 0; j < n; j++) {
			dp[i + arr[j]] = min(dp[i + arr[j]], dp[i] + 1);
		}
	}
	printf("%d\n", i - 1);
	return 0;
}
