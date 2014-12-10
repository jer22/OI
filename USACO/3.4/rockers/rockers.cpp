/*
ID:shijiey1
PROG:rockers
LANG:C++
*/

/*
dp[i][j][k]:考虑了前i首歌，装进了j张cd，最后一张cd用了k分钟能装下的最多的歌曲的数目。
初始状态：dp[1][1][0]=0，dp[1][1][arr[1]=1(arr[1]<=t)
转移(顺推)：dp[i + 1][j][k] = max(dp[i][j][k], dp[i + 1][j][k]) (不装第下一张cd)
dp[i + 1][j + 1][arr[i + 1]] = max(dp[i][j][k] + 1, dp[i + 1][j + 1][arr[i + 1]]) (arr[i+1]<=t) (将下一张cd装进一张新唱片)
dp[i + 1][j][arr[i + 1] + k] = max(dp[i][j][k] + 1, dp[i + 1][j][arr[i + 1] + k]) (arr[i+1]+k<=t) (将下一张唱片装进当前唱片)
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, t, m;
int arr[25];
int dp[25][25][25];
int main() {
	freopen("rockers.in", "r", stdin);
	freopen("rockers.out", "w", stdout);
	scanf("%d %d %d", &n, &t, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	memset(dp, -1, sizeof(dp));
	dp[1][1][0] = 0;
	if (arr[1] <= t) {
		dp[1][1][arr[1]] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			for (int k = 0; k <= t; k++) {
				if (dp[i][j][k] == -1) continue;
				dp[i + 1][j][k] = max(dp[i][j][k], dp[i + 1][j][k]);
				if (arr[i + 1] <= t) {
					dp[i + 1][j + 1][arr[i + 1]] = max(dp[i][j][k] + 1, dp[i + 1][j + 1][arr[i + 1]]);
				}
				if (arr[i + 1] + k <= t) {
					dp[i + 1][j][arr[i + 1] + k] = max(dp[i][j][k] + 1, dp[i + 1][j][arr[i + 1] + k]);
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= m; j++) {
			ans = max(ans, dp[n][j][i]);
		}
	}
	printf("%d\n", ans);
	return 0;
}
