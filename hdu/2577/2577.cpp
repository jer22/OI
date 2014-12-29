#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
char str[111];
int dp[111][2];
int main() {
	freopen("2577.in", "r", stdin);
	scanf("%d\n", &T);
	while (T--) {
		scanf("%s", str);
		memset(dp, 0x3f, sizeof(dp));
		dp[0][1] = 1;
		dp[0][0] = 0;
		int n = strlen(str);
		for (int i = 1; i <= n; i++) {
			dp[i][0] = min(dp[i][0], dp[i - 1][1] + 2);
			dp[i][1] = min(dp[i][1], dp[i - 1][0] + 2);
			if (str[i - 1] >= 'a' && str[i - 1] <= 'z') {
				dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
				dp[i][1] = min(dp[i][1], dp[i - 1][1] + 2);
			} else {
				dp[i][0] = min(dp[i][0], dp[i - 1][0] + 2);
				dp[i][1] = min(dp[i][1], dp[i - 1][1] + 1);
			}
		}
		printf("%d\n", dp[n][0]);
	}
	return 0;
}
