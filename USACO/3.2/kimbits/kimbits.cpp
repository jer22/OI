/*
ID:shijiey1
PROB:kimbits
LANG:C++
*/

/*
dp[j][k]表示长度为j的串中有不多与k个1的个数
所以dp[j][k] = dp[j][k-1]+c[j][k].
边界：dp[j][0]=dp[0][j]=1
然后从n到1枚举k，每次输出所求串的从右到左第k位。
如果dp[k-1][l]<I,说明当前位一定是1，否则后面全填1也取不到第I个。此时这一位填了1，代表已经取完了前dp[k-1][l]个数，现在还剩i - dp[k - 1][l]个数，所以i -= dp[k - 1][l]。
如果dp[k-1][l]>=I,则这一位一定填0，原因类似上面。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

long long n, l, i;
long long c[35][35];
long long dp[35][35];
int main() {
	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);
	scanf("%lld %lld %lld", &n, &l, &i);
	for (int j = 0; j <= n; j++) {
		c[j][0] = dp[0][j] = 1;
	}
	for (int j = 1; j <= n; j++) {
		for (int k = 1; k <= j; k++) {
			c[j][k] = c[j - 1][k] + c[j - 1][k - 1];
		}
	}
	for (int j = 1; j <= n; j++) {
		dp[j][0] = 1;
		for (int k = 1; k <= n; k++)
			dp[j][k] = dp[j][k-1] + c[j][k];
	}
	for (int k = n; k >= 1; k--) {
		if (dp[k - 1][l] < i) {
			cout << '1';
			i -= dp[k - 1][l];
			l--;
		} else {
			cout << '0';
		}
	}
	cout << endl;
	return 0;
}
