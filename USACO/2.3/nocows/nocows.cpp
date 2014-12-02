/*
ID:shijiey1
PROG:nocows
LANG:C++
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
