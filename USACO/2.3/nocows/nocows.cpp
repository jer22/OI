/*
ID:shijiey1
PROG:nocows
LANG:C++
*/

/*
dp[k][n]表示节点数为n，高度不大于k的结构数。
初始状态：dp[i][1]=1
转移：dp[k][n] = ∑(dp[k - 1][s] * dp[k - 1][n - s - 1]) (s = 1 to n-2)
因为对于每一棵树T都可以分解为根节点与两个子树T1，T2，高度均不大与k-1，节点数之和s1+s2=n-1，结构数为p1，p2。
对于每一组不同的s1,s2，T的结构数即p=p1*p2。
所以T的总结构数就是对于所有不同的s1，s2的p的和即dp[k][n] = ∑(dp[k - 1][s] * dp[k - 1][n - s - 1]) (s = 1 to n-2)
注意状态是节点数为n，高度“不大与”k的结构数。
所以最后结果为dp[k][n] - dp[k - 1][n]。
注意随时取模，还有就是最后减的时候可能减到负数，所以应该(dp[k][n] - dp[k - 1][n] + 9901) % 9901)。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, k;
int dp[210][210];
int main() {
	freopen("nocows.in", "r", stdin);
	freopen("nocows.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= k; i++) {
		dp[i][1] = 1;
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 3; j <= n; j++) {
			for (int s = 1; s <= j - 2; s++) {
				dp[i][j] += (dp[i - 1][s] * dp[i - 1][j - s - 1]);
				dp[i][j] %= 9901;
			}
		}
	}
	printf("%d\n", (dp[k][n] - dp[k - 1][n] + 9901) % 9901);
	return 0;
}
